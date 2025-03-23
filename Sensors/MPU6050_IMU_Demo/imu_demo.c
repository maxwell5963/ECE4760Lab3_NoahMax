/**
 * V. Hunter Adams (vha3@cornell.edu)
 * 
 * This demonstration utilizes the MPU6050.
 * It gathers raw accelerometer/gyro measurements, scales
 * them, and plots them to the VGA display. The top plot
 * shows gyro measurements, bottom plot shows accelerometer
 * measurements.
 * 
 * HARDWARE CONNECTIONS
 *  - GPIO 16 ---> VGA Hsync
 *  - GPIO 17 ---> VGA Vsync
 *  - GPIO 18 ---> 330 ohm resistor ---> VGA Red
 *  - GPIO 19 ---> 330 ohm resistor ---> VGA Green
 *  - GPIO 20 ---> 330 ohm resistor ---> VGA Blue
 *  - RP2040 GND ---> VGA GND
 *  - GPIO 8 ---> MPU6050 SDA
 *  - GPIO 9 ---> MPU6050 SCL
 *  - 3.3v ---> MPU6050 VCC
 *  - RP2040 GND ---> MPU6050 GND
 */


// Include standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// Include PICO libraries
#include "pico/stdlib.h"
#include "pico/multicore.h"
// Include hardware libraries
#include "hardware/pwm.h"
#include "hardware/dma.h"
#include "hardware/irq.h"
#include "hardware/adc.h"
#include "hardware/pio.h"
#include "hardware/i2c.h"
// Include custom libraries
#include "vga16_graphics.h"
#include "mpu6050.h"
#include "pt_cornell_rp2040_v1_3.h"


// Arrays in which raw measurements will be stored
fix15 acceleration[3], gyro[3];

// character array
char screentext[40];

// draw speed
int threshold = 10 ;

// Some macros for max/min/abs
#define min(a,b) ((a<b) ? a:b)
#define max(a,b) ((a<b) ? b:a)
#define abs(a) ((a>0) ? a:-a)

// semaphore
static struct pt_sem vga_semaphore ;

// Some paramters for PWM
#define WRAPVAL 5000
#define CLKDIV  25.0
uint slice_num ;

// Global/static variables for PID and plotting
static float pitch_deg = 0.0f;      // Filtered angle
static float target_angle = 0.0f;   // User-set target angle
static float integral = 0.0f;       // Accumulated integral error
static float prev_error = 0.0f;     // Previous error for derivative term
static float motor_command = 0.0f;  // Stores PID output for plotting
static float error = 0.0f;          // Stores error for plotting
static float derivative = 0.0f;     // Stores derivative term for plotting
static uint16_t motor_disp = 0;     // Filtered motor command for display

// Fixed-point complementary angle (15.16 format)
static int complementary_angle = 0;

// PID Constants (TUNE THESE)
static float Kp = 1.5;  
static float Ki = 0.01; 
static float Kd = 0.5;

// Gyro bias correction
static float gyro_bias_x = 0.5f;  // Adjust this value based on calibration

// Complementary filter weights
// Using 0.001 for accelerometer and 0.999 for gyro as recommended
#define ACCEL_WEIGHT 0.001f
#define GYRO_WEIGHT 0.999f

// Interrupt service routine
void on_pwm_wrap() {
    pwm_clear_irq(pwm_gpio_to_slice_num(5));
    mpu6050_read_raw(acceleration, gyro);

    // Convert fix15 to float for calculations
    float ax = fix2float15(acceleration[0]);
    float ay = fix2float15(acceleration[1]);
    float az = fix2float15(acceleration[2]);
    
    // Use X-axis consistently for gyro (adjust if your mounting orientation differs)
    float gx = fix2float15(gyro[0]);
    
    // Apply gyro bias correction
    float gx_corrected = gx - gyro_bias_x;

    // Time step for integration
    float dt = 0.001f;  // 1ms

    // Calculate accelerometer angle without small angle approximation
    // Using the fixed-point calculations as per the tutorial
    int accel_angle = multfix15(float2fix15(atan2(-ay, az) + 3.1415f), oneeightyoverpi);
    
    // Calculate gyro angle delta (measurement times timestep)
    int gyro_angle_delta = multfix15(gyro[0], zeropt001);
    
    // Compute complementary filter - fixed point method
    // Alpha = 0.999 for gyro (high-pass) and (1-alpha) = 0.001 for accelerometer (low-pass)
    complementary_angle = multfix15(complementary_angle - gyro_angle_delta, zeropt999) + 
                          multfix15(accel_angle, zeropt001);
    
    // Convert the fixed-point complementary angle to float for the PID controller
    pitch_deg = fix2float15(complementary_angle);

    // Compute PID terms
    error = target_angle - pitch_deg;
    integral += error * dt; 
    derivative = (error - prev_error) / dt;
    prev_error = error;

    // Compute PID output
    motor_command = (Kp * error) + (Ki * integral) + (Kd * derivative);

    // Convert PID output to PWM duty cycle
    uint16_t pwm_value = (uint16_t)(motor_command * 500 + 2500);

    // Apply low-pass filter to motor signal (16-sample smoothing - time constant as recommended)
    motor_disp = motor_disp + ((pwm_value - motor_disp) >> 4); // Using 4 for shift (2^4 = 16)

    // Limit motor power
    if (motor_disp > 5000) motor_disp = 5000;
    if (motor_disp < 0) motor_disp = 0;

    // Set motor PWM duty cycle using filtered value
    pwm_set_chan_level(slice_num, PWM_CHAN_A, motor_disp);

    // Signal VGA update
    PT_SEM_SIGNAL(pt, &vga_semaphore);
}


// Thread that draws to VGA display
static PT_THREAD (protothread_vga(struct pt *pt)) {
    PT_BEGIN(pt);

    static int xcoord = 81;  
    static int throttle;
    // Range for angle display from 0 to 180 degrees
    static float OldRange = 180.0;  
    static float NewRange = 150.0; // Display height in pixels
    static float OldMin = 0.0;     // Starting at 0 degrees

    setTextSize(1);
    setTextColor(WHITE);
    
    // Draw the static graph grid
    drawHLine(75, 230, 5, CYAN);  // Bottom line (0 degrees)
    drawHLine(75, 155, 5, CYAN);  // Middle line (90 degrees)
    drawHLine(75, 80, 5, CYAN);   // Top line (180 degrees)
    drawVLine(80, 80, 150, CYAN); // Vertical axis
    
    // Add labels for the angle axis
    setCursor(50, 80); 
    writeString("180");
    setCursor(50, 155); 
    writeString("90");
    setCursor(50, 230); 
    writeString("0");
    
    // Add a second vertical axis for motor command
    drawVLine(610, 80, 150, GREEN);
    setCursor(615, 80);
    writeString("5000");
    setCursor(615, 155);
    writeString("2500");
    setCursor(615, 230);
    writeString("0");

    while (true) {
        PT_SEM_WAIT(pt, &vga_semaphore);
        throttle += 1;

        if (throttle >= threshold) { 
            throttle = 0;  

            // Erase previous column to keep graph clean
            drawVLine(xcoord, 0, 480, BLACK);

            // Make sure pitch_deg is within 0-180 range for display
            float display_angle = pitch_deg;
            if (display_angle < 0) display_angle = 0;
            if (display_angle > 180) display_angle = 180;
            
            // Plot actual angle from complementary filter (pitch_deg)
            drawPixel(xcoord, 230 - (int)(NewRange * ((display_angle - OldMin) / OldRange)), WHITE);

            // Plot target angle (target_angle)
            drawPixel(xcoord, 230 - (int)(NewRange * ((target_angle - OldMin) / OldRange)), RED);
            
            // Plot motor command (scaled to fit the display)
            // motor_disp range is 0-5000, map to 80-230 pixel range
            int motor_y = 230 - (int)((motor_disp / 5000.0) * 150.0);
            drawPixel(xcoord, motor_y, GREEN);

            // Scroll horizontally for real-time effect
            if (xcoord < 609) {
                xcoord += 1;
            } else {
                xcoord = 81; 
            }

            // Clear old text by drawing black rectangles
            #define TEXT_BG_WIDTH  140
            #define TEXT_BG_HEIGHT 10

            fillRect(10, 10, TEXT_BG_WIDTH, TEXT_BG_HEIGHT, RED);
            setCursor(10, 10); setTextColor(WHITE);
            sprintf(screentext, "P: %.2f", Kp * error);
            writeString(screentext);

            fillRect(10, 30, TEXT_BG_WIDTH, TEXT_BG_HEIGHT, RED);
            setCursor(10, 30); setTextColor(YELLOW);
            sprintf(screentext, "I: %.2f", Ki * integral);
            writeString(screentext);

            fillRect(10, 50, TEXT_BG_WIDTH, TEXT_BG_HEIGHT, RED);
            setCursor(10, 50); setTextColor(MAGENTA);
            sprintf(screentext, "D: %.2f", Kd * derivative);
            writeString(screentext);

            fillRect(10, 70, TEXT_BG_WIDTH, TEXT_BG_HEIGHT, RED);
            setCursor(10, 70); setTextColor(GREEN);
            sprintf(screentext, "Motor Cmd: %.2f", motor_command);
            writeString(screentext);
            
            fillRect(10, 90, TEXT_BG_WIDTH, TEXT_BG_HEIGHT, RED);
            setCursor(10, 90); setTextColor(WHITE);
            sprintf(screentext, "Angle: %.2f", pitch_deg);
            writeString(screentext);
            
            fillRect(10, 110, TEXT_BG_WIDTH, TEXT_BG_HEIGHT, RED);
            setCursor(10, 110); setTextColor(GREEN);
            sprintf(screentext, "Filtered PWM: %d", motor_disp);
            writeString(screentext);
        }
    }
    PT_END(pt);
}

// User input thread. User can change draw speed
static PT_THREAD (protothread_serial(struct pt *pt))
{
    PT_BEGIN(pt) ;
    static char classifier ;
    static int test_in ;
    static float float_in ;
    while(1) {
        sprintf(pt_serial_out_buffer, "input a command: ");
        serial_write ;
        // spawn a thread to do the non-blocking serial read
        serial_read ;
        // convert input string to number
        sscanf(pt_serial_in_buffer,"%c", &classifier) ;

        // num_independents = test_in ;
        if (classifier=='t') {
            sprintf(pt_serial_out_buffer, "timestep: ");
            serial_write ;
            serial_read ;
            // convert input string to number
            sscanf(pt_serial_in_buffer,"%d", &test_in) ;
            if (test_in > 0) {
                threshold = test_in ;
            }
        }
    }
    PT_END(pt) ;
}

// Entry point for core 1
void core1_entry() {
    pt_add_thread(protothread_vga) ;
    pt_schedule_start ;
}

int main() {

    // Initialize stdio
    stdio_init_all();

    // Initialize VGA
    initVGA() ;

    ////////////////////////////////////////////////////////////////////////
    ///////////////////////// I2C CONFIGURATION ////////////////////////////
    i2c_init(I2C_CHAN, I2C_BAUD_RATE) ;
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C) ;
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C) ;

    // Pullup resistors on breakout board, don't need to turn on internals
    // gpio_pull_up(SDA_PIN) ;
    // gpio_pull_up(SCL_PIN) ;

    // MPU6050 initialization
    mpu6050_reset();
    mpu6050_read_raw(acceleration, gyro);

    ////////////////////////////////////////////////////////////////////////
    ///////////////////////// PWM CONFIGURATION ////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    // Tell GPIO's 4,5 that they allocated to the PWM
    gpio_set_function(5, GPIO_FUNC_PWM);
    gpio_set_function(4, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to GPIO 5 (it's slice 2, same for 4)
    slice_num = pwm_gpio_to_slice_num(5);

    // Mask our slice's IRQ output into the PWM block's single interrupt line,
    // and register our interrupt handler
    pwm_clear_irq(slice_num);
    pwm_set_irq_enabled(slice_num, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
    irq_set_enabled(PWM_IRQ_WRAP, true);

    // This section configures the period of the PWM signals
    pwm_set_wrap(slice_num, WRAPVAL) ;
    pwm_set_clkdiv(slice_num, CLKDIV) ;

    // This sets duty cycle
    pwm_set_chan_level(slice_num, PWM_CHAN_B, 0);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 0);

    // Start the channel
    pwm_set_mask_enabled((1u << slice_num));


    ////////////////////////////////////////////////////////////////////////
    ///////////////////////////// ROCK AND ROLL ////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    // start core 1 
    multicore_reset_core1();
    multicore_launch_core1(core1_entry);

    // start core 0
    pt_add_thread(protothread_serial) ;
    pt_schedule_start ;

}
