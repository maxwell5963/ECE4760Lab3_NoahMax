/**
 * V. Hunter Adams (vha3@cornell.edu)
 *
 * This demonstration reads data from the MPU6050, applies a PID controller,
 * and displays the processed data on a VGA screen. The top graph shows angle
 * information while the bottom graph shows accelerometer readings.
 *
 * HARDWARE CONNECTIONS:
 *  - GPIO 16 ---> VGA Hsync
 *  - GPIO 17 ---> VGA Vsync
 *  - GPIO 18 ---> VGA Red (via 330Ω resistor)
 *  - GPIO 19 ---> VGA Green (via 330Ω resistor)
 *  - GPIO 20 ---> VGA Blue (via 330Ω resistor)
 *  - RP2040 GND ---> VGA GND
 *  - GPIO 8  ---> MPU6050 SDA
 *  - GPIO 9  ---> MPU6050 SCL
 *  - 3.3V    ---> MPU6050 VCC
 *  - RP2040 GND ---> MPU6050 GND
 */

// Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// PICO libraries
#include "pico/stdlib.h"
#include "pico/multicore.h"

// Hardware libraries
#include "hardware/pwm.h"
#include "hardware/irq.h"
#include "hardware/i2c.h"

// Custom libraries
#include "vga16_graphics.h"
#include "mpu6050.h"
#include "pt_cornell_rp2040_v1_3.h"

// Data arrays (fixed-point 15.16)
fix15 rawAccel[3], smoothAccel[3], gyroVals[3];

#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2
#define GYRO_X 0
#define GYRO_Y 1
#define GYRO_Z 2

// PID constants (fixed-point)
fix15 Kp = int2fix15(240);
fix15 Ki = int2fix15(80);
fix15 Kd = int2fix15(40);

fix15 integralSum = 0;
fix15 lastErr = 0;

fix15 angleFromAccel = 0;
fix15 gyroAngleChange = 0;
fix15 fusedAngle = 0;
fix15 targetAngle = int2fix15(0);
int pwmValue = 0;

// Buffer for text output on VGA
char textBuffer[40];

// Update rate for drawing (lower value = faster updates)
int drawRate = 10;

// Simple macros for min/max/abs
#define MIN_VAL(a,b) ((a) < (b) ? (a) : (b))
#define MAX_VAL(a,b) ((a) < (b) ? (b) : (a))
#define ABS_VAL(a) ((a) < 0 ? -(a) : (a))

// Semaphore for VGA thread synchronization
static struct pt_sem vgaSem;

// PWM configuration constants
#define PWM_TOP 5000
#define PWM_DIVIDER 25.0
uint pwmSlice;

// Interrupt handler: triggered when PWM counter wraps.
void pwmWrapISR() {
    pwm_clear_irq(pwm_gpio_to_slice_num(5));

    // Read sensor data from MPU6050.
    mpu6050_read_raw(rawAccel, gyroVals);

    // Apply a simple low-pass filter.
    smoothAccel[0] += (rawAccel[0] - smoothAccel[0]) >> 3;
    smoothAccel[1] += (rawAccel[1] - smoothAccel[1]) >> 3;
    smoothAccel[2] += (rawAccel[2] - smoothAccel[2]) >> 3;
    
    // Compute angle from accelerometer data.
    angleFromAccel = multfix15(float2fix15(atan2(-smoothAccel[AXIS_Y], smoothAccel[AXIS_Z]) + (M_PI/2.0)), oneeightyoverpi);
    gyroAngleChange = multfix15(gyroVals[GYRO_X], zeropt001);
    fusedAngle = multfix15(fusedAngle - gyroAngleChange, zeropt999) +
                 multfix15(angleFromAccel, zeropt001);

    // PID calculation (no feed-forward).
    const fix15 err = targetAngle - fusedAngle;
    const fix15 deriv = (err - lastErr) * 1000;
    lastErr = err;
    integralSum += err / 1000;

    // Anti-windup for the integral term.
    fix15 integralLimit = divfix(int2fix15(25), Ki);
    if (integralSum > integralLimit)
        integralSum = integralLimit;
    else if (integralSum < -integralLimit)
        integralSum = -integralLimit;

    const fix15 pidOut = multfix15(Kp, err) + multfix15(Ki, integralSum) + multfix15(Kd, deriv);
    int newPWM = fix2int15(pidOut);
    if (newPWM < 0) newPWM = 0;
    if (newPWM > 3000) newPWM = 3000;

    // Smooth changes in PWM output.
    //if (newPWM != pwmValue) {
      //  if (newPWM > pwmValue)
        //    pwmValue = MIN_VAL(newPWM, pwmValue + 100);
        //else
       //     pwmValue = MAX_VAL(newPWM, pwmValue - 100);
    pwm_set_chan_level(pwmSlice, PWM_CHAN_A, newPWM);
    //}

    // Signal the VGA thread to update the display.
    PT_SEM_SIGNAL(pt, &vgaSem);
}

// Thread to simulate button-triggered target angle changes.
static PT_THREAD(buttonTask(struct pt *pt)) {
    PT_BEGIN(pt);
    static int btnState = 0, lastState = 0;
    while (true) {
        btnState = !gpio_get(15);
        if (!btnState && lastState) {
            targetAngle = int2fix15(-45);
            PT_YIELD_usec(5000000);
            targetAngle = int2fix15(-15);
            PT_YIELD_usec(5000000);
            targetAngle = int2fix15(-75);
            PT_YIELD_usec(5000000);
            targetAngle = int2fix15(-45);
            PT_YIELD_usec(5000000);
            targetAngle = int2fix15(0);
        }
        lastState = btnState;
        PT_YIELD_usec(100000);
    }
    PT_END(pt);
}

// VGA drawing thread with updated color choices.
// Top graph uses: targetAngle in CYAN, fusedAngle in MAGENTA, accel-derived angle in YELLOW,
// and gyro delta in WHITE.
// Bottom graph uses: smoothAccel[0] in MAGENTA, smoothAccel[1] in BLUE, smoothAccel[2] in CYAN.
static PT_THREAD(vgaTask(struct pt *pt)) {
    PT_BEGIN(pt);
    static int xPos = 81;
    static float oldRange = 500.0, newRange = 150.0;
    static float oldMin = -250.0;
    static int counter = 0;

    // Draw static elements (axes and labels) for both graphs.
    setTextSize(1);
    setTextColor(WHITE);
    drawHLine(75, 430, 5, CYAN);
    drawHLine(75, 355, 5, CYAN);
    drawHLine(75, 280, 5, CYAN);
    drawVLine(80, 280, 150, CYAN);
    sprintf(textBuffer, "0");
    setCursor(50, 350);
    writeString(textBuffer);
    sprintf(textBuffer, "+2");
    setCursor(50, 280);
    writeString(textBuffer);
    sprintf(textBuffer, "-2");
    setCursor(50, 425);
    writeString(textBuffer);

    drawHLine(75, 230, 5, CYAN);
    drawHLine(75, 155, 5, CYAN);
    drawHLine(75, 80, 5, CYAN);
    drawVLine(80, 80, 150, CYAN);
    sprintf(textBuffer, "0");
    setCursor(50, 150);
    writeString(textBuffer);
    sprintf(textBuffer, "+180");
    setCursor(45, 75);
    writeString(textBuffer);
    sprintf(textBuffer, "-180");
    setCursor(45, 225);
    writeString(textBuffer);

    while (true) {
        PT_SEM_WAIT(pt, &vgaSem);
        counter++;
        if (counter >= drawRate) {
            counter = 0;
            // Clear the current drawing column.
            drawVLine(xPos, 0, 480, BLACK);

            // Display PID parameters at the top-left of the screen.
            setTextColor2(WHITE, BLACK);
            char pidStr[256];
            sprintf(pidStr, "P: %d | I: %d | D: %d        ", fix2int15(Kp), fix2int15(Ki), fix2int15(Kd));
            setTextSize(2);
            setCursor(4, 4);
            writeStringBig(pidStr);

            // Display PID parameters at the top-left of the screen.
            setTextColor2(WHITE, BLACK);
            char anglestr[256];
            sprintf(anglestr, "Current Angle: %d | Desired Angle: %d ", fix2int15(fusedAngle), fix2int15(targetAngle));
            setTextSize(2);
            setCursor(4, 20);
            writeStringBig(anglestr);

            // Bottom graph: plot accelerometer data with new colors.
            drawPixel(xPos, 430 - (int)(newRange * (((fix2float15(smoothAccel[0]) * 120.0) - oldMin) / oldRange)), MAGENTA);
            drawPixel(xPos, 430 - (int)(newRange * (((fix2float15(smoothAccel[1]) * 120.0) - oldMin) / oldRange)), BLUE);
            drawPixel(xPos, 430 - (int)(newRange * (((fix2float15(smoothAccel[2]) * 120.0) - oldMin) / oldRange)), CYAN);

            // Top graph: plot angle data with new colors.
            drawPixel(xPos, 230 - (int)(newRange * ((fix2float15(targetAngle) - oldMin) / oldRange)), CYAN);    // target angle
            drawPixel(xPos, 230 - (int)(newRange * ((fix2float15(fusedAngle) - oldMin) / oldRange)), MAGENTA); // fused angle
            drawPixel(xPos, 230 - (int)(newRange * ((fix2float15(angleFromAccel) - oldMin) / oldRange)), YELLOW); // accel angle
            drawPixel(xPos, 230 - (int)(newRange * ((fix2float15(gyroAngleChange) - oldMin) / oldRange)), WHITE);  // gyro delta

            // Move the drawing cursor.
            xPos = (xPos < 609) ? xPos + 1 : 81;
        }
    }
    PT_END(pt);
}

// Serial thread for modifying PID constants and draw rate.
static PT_THREAD(serialTask(struct pt *pt)) {
    PT_BEGIN(pt);
    static char command;
    static int newRate;
    static float newVal;

    while (1) {
        // New prompt "ctrlcmd" for serial input.
        sprintf(pt_serial_out_buffer, "\n\rCurrent PWM Value: %d\n\rEnter Command [ctrlcmd]: ", pwmValue);
        serial_write;
        serial_read;
        sscanf(pt_serial_in_buffer, "%c", &command);

        if (command == 't') {
            sprintf(pt_serial_out_buffer, "\n\rCurrent Draw Rate: %d\n\rNew Draw Rate: ", drawRate);
            serial_write;
            serial_read;
            sscanf(pt_serial_in_buffer, "%d", &newRate);
            if (newRate > 0) drawRate = newRate;
        } else if (command == 'p') {
            float curP = fix2float15(Kp);
            sprintf(pt_serial_out_buffer, "\n\rCurrent P: %f\n\rNew P: ", curP);
            serial_write;
            serial_read;
            sscanf(pt_serial_in_buffer, "%f", &newVal);
            Kp = float2fix15(newVal);
        } else if (command == 'i') {
            float curI = fix2float15(Ki);
            sprintf(pt_serial_out_buffer, "\n\rCurrent I: %f\n\rNew I: ", curI);
            serial_write;
            serial_read;
            sscanf(pt_serial_in_buffer, "%f", &newVal);
            Ki = float2fix15(newVal);
        } else if (command == 'd') {
            float curD = fix2float15(Kd);
            sprintf(pt_serial_out_buffer, "\n\rCurrent D: %f\n\rNew D: ", curD);
            serial_write;
            serial_read;
            sscanf(pt_serial_in_buffer, "%f", &newVal);
            Kd = float2fix15(newVal);
        } else if (command == 'a') {
            float currAng = fix2float15(targetAngle);
            sprintf(pt_serial_out_buffer, "\n\rCurrent Target Angle: %f\n\rNew Target Angle: ", currAng);
            serial_write;
            serial_read;
            sscanf(pt_serial_in_buffer, "%f", &newVal);
            targetAngle = float2fix15(newVal);
        }
    }
    PT_END(pt);
}

// Core 1 entry: runs the VGA drawing thread.
void core1_main() {
    pt_add_thread(vgaTask);
    pt_schedule_start;
}

int main() {
    stdio_init_all();
    initVGA();

    // I2C configuration for MPU6050.
    i2c_init(I2C_CHAN, I2C_BAUD_RATE);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);

    // Initialize MPU6050.
    mpu6050_reset();
    mpu6050_read_raw(smoothAccel, gyroVals);

    // PWM configuration on GPIO 5 and 4.
    gpio_set_function(5, GPIO_FUNC_PWM);
    gpio_set_function(4, GPIO_FUNC_PWM);
    pwmSlice = pwm_gpio_to_slice_num(5);
    pwm_clear_irq(pwmSlice);
    pwm_set_irq_enabled(pwmSlice, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, pwmWrapISR);
    irq_set_enabled(PWM_IRQ_WRAP, true);
    pwm_set_wrap(pwmSlice, PWM_TOP);
    pwm_set_clkdiv(pwmSlice, PWM_DIVIDER);
    pwm_set_chan_level(pwmSlice, PWM_CHAN_B, 0);
    pwm_set_chan_level(pwmSlice, PWM_CHAN_A, 0);
    pwm_set_output_polarity(pwmSlice, 1, 0);
    pwm_set_mask_enabled((1u << pwmSlice));

    // Launch the VGA drawing thread on core 1.
    multicore_reset_core1();
    multicore_launch_core1(core1_main);

    // Add serial and button threads to core 0.
    pt_add_thread(serialTask);
    pt_add_thread(buttonTask);
    pt_schedule_start;
}
