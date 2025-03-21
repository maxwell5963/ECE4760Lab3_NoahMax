/**
 * MPU6050 Complementary Filter & PID Control with VGA Plotting
 * 
 * Implements a complementary filter using fixed-point math to estimate pitch angle.
 * The estimated angle is used in a PID controller to stabilize a helicopter arm.
 * The results are displayed on a VGA screen.
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

// Arrays to store raw IMU measurements
fix15 acceleration[3], gyro[3];

// Screen text buffer
char screentext[40];

// Drawing speed control
int threshold = 10;

// Semaphore for VGA update
static struct pt_sem vga_semaphore;

// PWM Configuration
#define WRAPVAL 5000
#define CLKDIV  25.0
uint slice_num;

// ===================== Complementary Filter Constants =====================
// Fixed-point constants
static fix15 complementary_angle = int2fix15(0);  // Complementary filter output
static fix15 accel_angle_fix15 = int2fix15(0);    // Accelerometer-based angle
static fix15 gyro_angle_delta = int2fix15(0);     // Change in gyro angle

// Fixed-point scaling factors
static fix15 zeropt001 = float2fix15(0.001);      // 0.001 (dt)
static fix15 zeropt999 = float2fix15(0.999);      // 0.999 (gyro weight)
static fix15 oneeightyoverpi = float2fix15(180.0 / M_PI); // Conversion factor for degrees

// ===================== PID Control Variables =====================
static float pitch_deg = 0.0f;      // Filtered angle (for plotting & PID)
static float target_angle = 0.0f;   // User-defined target angle
static float integral = 0.0f;       // Integral term in PID
static float prev_error = 0.0f;     // Previous error for derivative calculation
static float motor_command = 0.0f;  // PID output (used for motor control)
static float error = 0.0f;          // Current error
static float derivative = 0.0f;     // Derivative term

// PID Constants (TUNE THESE)
static float Kp = 1.5;  
static float Ki = 0.01; 
static float Kd = 0.5;

// ===================== INTERRUPT HANDLER =====================
void on_pwm_wrap() {
    pwm_clear_irq(pwm_gpio_to_slice_num(5));
    mpu6050_read_raw(acceleration, gyro);

    // ===================== Convert Fix15 to Floats =====================
    fix15 ax = acceleration[0];
    fix15 ay = acceleration[1];
    fix15 az = acceleration[2];
    fix15 gx = gyro[0];

    // ===================== Compute Accelerometer-based Angle =====================
    // SMALL ANGLE APPROXIMATION
    accel_angle_fix15 = multfix15(divfix(ax, ay), oneeightyoverpi);

    // NO SMALL ANGLE APPROXIMATION (Uncomment if needed)
    // accel_angle_fix15 = multfix15(float2fix15(atan2(-fix2float15(ax), fix2float15(ay)) + M_PI), oneeightyoverpi);

    // ===================== Compute Gyro Angle Change =====================
    gyro_angle_delta = multfix15(gyro[2], zeropt001); 

    // ===================== Apply Complementary Filter =====================
    complementary_angle = multfix15(complementary_angle - gyro_angle_delta, zeropt999) + multfix15(accel_angle_fix15, zeropt001);

    // Convert filtered complementary angle back to float
    pitch_deg = fix2float15(complementary_angle);

    // ===================== PID Controller =====================
    error = target_angle - pitch_deg;
    integral += error * 0.001; 
    derivative = (error - prev_error) / 0.001;
    prev_error = error;

    // Compute PID output
    motor_command = (Kp * error) + (Ki * integral) + (Kd * derivative);

    // Convert PID output to PWM duty cycle
    uint16_t pwm_value = (uint16_t)(motor_command * 500 + 2500);

    // Apply low-pass filter to motor signal (64-sample smoothing)
    static uint16_t motor_disp = 0;
    motor_disp = motor_disp + ((pwm_value - motor_disp) >> 6);

    // Limit motor power
    if (motor_disp > 5000) motor_disp = 5000;
    if (motor_disp < 0) motor_disp = 0;

    // Set motor PWM duty cycle using filtered value
    pwm_set_chan_level(slice_num, PWM_CHAN_A, motor_disp);

    // Signal VGA update
    PT_SEM_SIGNAL(pt, &vga_semaphore);
}

// ===================== VGA DISPLAY THREAD =====================
static PT_THREAD (protothread_vga(struct pt *pt)) {
    PT_BEGIN(pt);

    static int xcoord = 81;  
    static int throttle;
    static float OldRange = 90.0;  
    static float NewRange = 180.0; 
    static float OldMin = -90.0;   

    setTextSize(1);
    setTextColor(WHITE);
    
    // Draw the static graph grid
    drawHLine(75, 230, 5, CYAN);  
    drawHLine(75, 155, 5, CYAN);  
    drawHLine(75, 80, 5, CYAN);   
    drawVLine(80, 80, 150, CYAN); 

    while (true) {
        PT_SEM_WAIT(pt, &vga_semaphore);
        throttle += 1;

        if (throttle >= threshold) { 
            throttle = 0;  

            // Erase previous column to keep graph clean
            drawVLine(xcoord, 0, 480, BLACK);

            // Plot actual angle from complementary filter
            drawPixel(xcoord, 230 - (int)(NewRange * ((pitch_deg - OldMin) / OldRange)), WHITE);

            // Plot target angle
            drawPixel(xcoord, 230 - (int)(NewRange * ((target_angle - OldMin) / OldRange)), RED);

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

// ===================== MAIN FUNCTION =====================
int main() {
    stdio_init_all();
    initVGA();

    // I2C CONFIGURATION
    i2c_init(I2C_CHAN, I2C_BAUD_RATE);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    mpu6050_reset();
    mpu6050_read_raw(acceleration, gyro);

    // PWM CONFIGURATION
    gpio_set_function(5, GPIO_FUNC_PWM);
    gpio_set_function(4, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(5);
    pwm_clear_irq(slice_num);
    pwm_set_irq_enabled(slice_num, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
    irq_set_enabled(PWM_IRQ_WRAP, true);
    pwm_set_wrap(slice_num, WRAPVAL);
    pwm_set_clkdiv(slice_num, CLKDIV);
    pwm_set_mask_enabled((1u << slice_num));

    // START THREADS
    multicore_reset_core1();
    multicore_launch_core1(core1_entry);
    pt_add_thread(protothread_vga);
    pt_schedule_start;
}
