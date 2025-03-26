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
fix15 accel_raw[3], acceleration[3], gyro[3];

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

// Global/static variables for PID and plotting - all in fixed point (15.16 format)
fix15 complementary_angle = 0;  // Current angle in fixed point
fix15 target_angle = int2fix15(90);   // User-set target angle (default 90 degrees)
fix15 integral = 0;             // Accumulated integral error
fix15 prev_error = 0;           // Previous error for derivative term
fix15 error = 0;                // Error term for PID
fix15 derivative = 0;           // Derivative term for PID
fix15 pid_output = 0;           // Raw PID controller output
static uint16_t motor_disp = 0;        // Filtered motor command for display
fix15 gyro_angle_delta = 0;
fix15 accel_angle = 0;


// Fixed-point complementary angle (15.16 format)
//static int complementary_angle = 0;

// PID Constants (TUNE THESE)
static float kP = 1.5;  
static float kI = 0.01; 
static float kD = 0.5;

// Gyro bias correction
static float gyro_bias_x = 0.5f;  // Adjust this value based on calibration

// Complementary filter weights
// Using 0.001 for accelerometer and 0.999 for gyro as recommended
#define ACCEL_WEIGHT 0.001f
#define GYRO_WEIGHT 0.999f

// Interrupt service routine
// Interrupt service routine
void on_pwm_wrap() {
    // Clear the interrupt flag
    pwm_clear_irq(pwm_gpio_to_slice_num(5));
    
    // Read sensor data
    mpu6050_read_raw(acceleration, gyro);

    // Low-pass filter for raw readings
    acceleration[0] += (accel_raw[0] - acceleration[0]) >> 4;
    acceleration[1] += (accel_raw[1] - acceleration[1]) >> 4;
    acceleration[2] += (accel_raw[2] - acceleration[2]) >> 4;

    // Convert fix15 to float for calculations
    float ax = fix2float15(acceleration[0]);
    float ay = fix2float15(acceleration[1]);
    float az = fix2float15(acceleration[2]);
    
    // Calculate accelerometer angle without small angle approximation
    accel_angle = multfix15(float2fix15(atan2(-ay, az) + 3.1415f), oneeightyoverpi);
    
    // Calculate gyro angle delta (measurement times timestep)
    gyro_angle_delta = -multfix15(gyro[0], zeropt001);
    
    // Compute complementary filter - fixed point method
    // Alpha = 0.999 for gyro (high-pass) and (1-alpha) = 0.001 for accelerometer (low-pass)
    complementary_angle = multfix15(complementary_angle - gyro_angle_delta, zeropt999) + 
                          multfix15(accel_angle, zeropt001);
    
    // Compute PID terms
    error = target_angle - complementary_angle;
    derivative = (error - prev_error) * 1000;
    prev_error = error;

    // === Control signal computation (formerly in compute_control_signal) ===
    
    // Memory for past control value
    static int old_control = 0;
    
    // Accumulate error with scaling
    integral += error / 1000;
    
    // Anti-windup: if the integral term is too large, limit it
    fix15 max_integral = divfix(int2fix15(25), float2fix15(kI));
    if (integral > max_integral) {
        integral = max_integral;
    } else if (integral < -max_integral) {
        integral = -max_integral;
    }
    
    // Compute the PID controller output
    pid_output = multfix15(float2fix15(kP), error) + 
                 multfix15(float2fix15(kI), integral) + 
                 multfix15(float2fix15(kD), derivative);
    
    // Add feed-forward compensation for gravity
    fix15 sin_angle = float2fix15(sin(fix2float15(target_angle) * 3.1415 / 180.0));
    fix15 feed_forward = multfix15(sin_angle, int2fix15(1500));
    
    // Calculate final control value
    int control = fix2int15(pid_output + feed_forward);
    
    // Apply bounds
    if (control <= 0) control = 0;
    if (control >= 3000) control = 3000;
    
    // Apply rate limiting
    if (control != old_control) {
        if (control > old_control) {
            old_control = min(control, old_control + 100);
        } else {
            old_control = max(control, old_control - 100);
        }
        
        // Update PWM only if control value changed
        pwm_set_chan_level(slice_num, PWM_CHAN_A, old_control);
    }
    
    // Update motor display value
    motor_disp = old_control;
    
    // Signal VGA update
    PT_SEM_SIGNAL(pt, &vga_semaphore);
}


// Thread that draws to VGA display
// Thread that draws to VGA display
static PT_THREAD (protothread_vga(struct pt *pt))
{
    // Indicate start of thread
    PT_BEGIN(pt) ;

    // We will start drawing at column 81
    static int xcoord = 81 ;
    
    // Rescale the measurements for display
    static float OldRange = 500. ; // (+/- 250)
    static float NewRange = 150. ; // (looks nice on VGA)
    static float OldMin = -250. ;
    static float OldMax = 250. ;

    // Control rate of drawing
    static int throttle ;

    // Draw the static aspects of the display
    setTextSize(1) ;
    setTextColor(WHITE);

    // Draw bottom plot
    drawHLine(75, 430, 5, CYAN) ;
    drawHLine(75, 355, 5, CYAN) ;
    drawHLine(75, 280, 5, CYAN) ;
    drawVLine(80, 280, 150, CYAN) ;
    sprintf(screentext, "0") ;
    setCursor(50, 350) ;
    writeString(screentext) ;
    sprintf(screentext, "+2") ;
    setCursor(50, 280) ;
    writeString(screentext) ;
    sprintf(screentext, "-2") ;
    setCursor(50, 425) ;
    writeString(screentext) ;

    // Draw top plot
    drawHLine(75, 230, 5, CYAN) ;
    drawHLine(75, 155, 5, CYAN) ;
    drawHLine(75, 80, 5, CYAN) ;
    drawVLine(80, 80, 150, CYAN) ;
    sprintf(screentext, "0") ;
    setCursor(50, 150) ;
    writeString(screentext) ;
    sprintf(screentext, "+250") ;
    setCursor(45, 75) ;
    writeString(screentext) ;
    sprintf(screentext, "-250") ;
    setCursor(45, 225) ;
    writeString(screentext) ;
    

    while (true) {
        // Wait on semaphore
        PT_SEM_WAIT(pt, &vga_semaphore);
        // Increment drawspeed controller
        throttle += 1 ;
        // If the controller has exceeded a threshold, draw
        if (throttle >= threshold) { 
            // Zero drawspeed controller
            throttle = 0 ;

            // Erase a column
            drawVLine(xcoord, 0, 480, BLACK) ;

            setTextColor2(WHITE, BLACK) ;
            char pid_text[256] ;
            sprintf(pid_text, "kP: %d | kI: %d | kD: %d        ", 
                fix2int15(float2fix15(kP)), 
                fix2int15(float2fix15(kI)), 
                fix2int15(float2fix15(kD)));           
            setTextSize(2);
            setCursor(4, 4);
            writeStringBig(pid_text) ;
            
            // Draw bottom plot (multiply by 120 to scale from +/-2 to +/-250)
            drawPixel(xcoord, 430 - (int)(NewRange*((float)((fix2float15(acceleration[0])*120.0)-OldMin)/OldRange)), WHITE) ;
            drawPixel(xcoord, 430 - (int)(NewRange*((float)((fix2float15(acceleration[1])*120.0)-OldMin)/OldRange)), RED) ;
            drawPixel(xcoord, 430 - (int)(NewRange*((float)((fix2float15(acceleration[2])*120.0)-OldMin)/OldRange)), GREEN) ;

            // Draw top plot
            // drawPixel(xcoord, 230 - (int)(NewRange*((float)((fix2float15(gyro[0]))-OldMin)/OldRange)), WHITE) ;
            // drawPixel(xcoord, 230 - (int)(NewRange*((float)((fix2float15(gyro[1]))-OldMin)/OldRange)), RED) ;
            // drawPixel(xcoord, 230 - (int)(NewRange*((float)((fix2float15(gyro[2]))-OldMin)/OldRange)), GREEN) ;

            
            drawPixel(xcoord, 230 - (int)(NewRange*((float)((fix2float15(target_angle))-OldMin)/OldRange)), WHITE) ;
            drawPixel(xcoord, 230 - (int)(NewRange*((float)((fix2float15(complementary_angle))-OldMin)/OldRange)), RED) ;
            drawPixel(xcoord, 230 - (int)(NewRange*((float)((fix2float15(accel_angle))-OldMin)/OldRange)), GREEN) ;
            drawPixel(xcoord, 230 - (int)(NewRange*((float)((fix2float15(gyro_angle_delta))-OldMin)/OldRange)), BLUE) ;

            // Update horizontal cursor
            if (xcoord < 609) {
                xcoord += 1 ;
            }
            else {
                xcoord = 81 ;
            }
        }
    }
    // Indicate end of thread
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
