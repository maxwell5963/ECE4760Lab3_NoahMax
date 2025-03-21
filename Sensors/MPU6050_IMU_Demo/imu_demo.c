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
static float pitch_gyro_deg = 0.0f; // Integrated gyro angle
static float target_angle = 0.0f;   // User-set target angle
static float integral = 0.0f;       // Accumulated integral error
static float prev_error = 0.0f;     // Previous error for derivative term
static float motor_command = 0.0f;  // Stores PID output for plotting
static float error = 0.0f;          // Stores error for plotting
static float derivative = 0.0f;     // Stores derivative term for plotting

// PID Constants (TUNE THESE)
static float Kp = 1.5;  
static float Ki = 0.01; 
static float Kd = 0.5;


// Interrupt service routine
void on_pwm_wrap() {
    pwm_clear_irq(pwm_gpio_to_slice_num(5));
    mpu6050_read_raw(acceleration, gyro);

    // Convert fix15 to float
    float ax = fix2float15(acceleration[0]);
    float ay = fix2float15(acceleration[1]);
    float az = fix2float15(acceleration[2]);
    float gx = fix2float15(gyro[0]);

    // Correct for gyro bias
    float gyro_bias_x = 0.5;  
    float gx_corrected = gx - gyro_bias_x;

    // Calculate accelerometer-based pitch angle
    float pitch_acc_deg = atan2f(ay, sqrtf(ax * ax + az * az)) * (180.0f / M_PI);

    // Integrate the gyro reading
    float dt = 0.001;  
    pitch_gyro_deg += gx_corrected * dt;

    // Apply the complementary filter
    float alpha = 0.98;
    pitch_deg = alpha * pitch_gyro_deg + (1.0f - alpha) * pitch_acc_deg;

    // Compute PID terms
    error = target_angle - pitch_deg;
    integral += error * dt; 
    derivative = (error - prev_error) / dt;
    prev_error = error;

    // Compute PID output
    motor_command = (Kp * error) + (Ki * integral) + (Kd * derivative);

    // Convert PID output to PWM duty cycle
    uint16_t pwm_value = (uint16_t)(motor_command * 500 + 2500); 

    // Limit motor power
    if (pwm_value > 5000) pwm_value = 5000;
    if (pwm_value < 0) pwm_value = 0;

    // Set motor PWM duty cycle
    pwm_set_chan_level(slice_num, PWM_CHAN_A, pwm_value);

    // Signal VGA to update
    PT_SEM_SIGNAL(pt, &vga_semaphore);
}


// Thread that draws to VGA display
static PT_THREAD (protothread_vga(struct pt *pt)) {
    PT_BEGIN(pt);

    static int xcoord = 81;  
    static int throttle;
    static float OldRange = 90.0;  
    static float NewRange = 150.0; 
    static float OldMin = -45.0;   

    setTextSize(1);
    setTextColor(WHITE);
    drawHLine(75, 230, 5, CYAN);  
    drawHLine(75, 155, 5, CYAN);  
    drawHLine(75, 80, 5, CYAN);   
    drawVLine(80, 80, 150, CYAN); 

    while (true) {
        PT_SEM_WAIT(pt, &vga_semaphore);
        throttle += 1;

        if (throttle >= threshold) { 
            throttle = 0;  

            // Erase previous column
            drawVLine(xcoord, 0, 480, BLACK);

            // **Plot complementary filter output (`pitch_deg`)**
            drawPixel(xcoord, 230 - (int)(NewRange * ((pitch_deg - OldMin) / OldRange)), WHITE);

            // **Plot target angle (`target_angle`)**
            drawPixel(xcoord, 230 - (int)(NewRange * ((target_angle - OldMin) / OldRange)), RED);

            // **Plot PID output (`motor_command`)**
            drawPixel(xcoord, 430 - (int)(NewRange * ((motor_command - OldMin) / OldRange)), GREEN);

            // **Plot Proportional, Integral, and Derivative terms**
            drawPixel(xcoord, 230 - (int)(NewRange * ((Kp * error - OldMin) / OldRange)), BLUE);    
            drawPixel(xcoord, 230 - (int)(NewRange * ((Ki * integral - OldMin) / OldRange)), YELLOW);  
            drawPixel(xcoord, 230 - (int)(NewRange * ((Kd * derivative - OldMin) / OldRange)), MAGENTA);  

            // Scroll horizontally
            if (xcoord < 609) {
                xcoord += 1;
            } else {
                xcoord = 81; 
            }
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
