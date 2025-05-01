// main.c
/**
 * Hunter Adams (vha3@cornell.edu)
 *
 * This demonstration animates two balls bouncing about the screen.
 * Through a serial interface, the user can change the ball color.
 *
 * HARDWARE CONNECTIONS
 *  - GPIO 16 ---> VGA Hsync
 *  - GPIO 17 ---> VGA Vsync
 *  - GPIO 18 ---> 470 ohm resistor ---> VGA Green 
 *  - GPIO 19 ---> 330 ohm resistor ---> VGA Green
 *  - GPIO 20 ---> 330 ohm resistor ---> VGA Blue
 *  - GPIO 21 ---> 330 ohm resistor ---> VGA Red
 *  - RP2040 GND ---> VGA GND
 *
 * RESOURCES USED
 *  - PIO state machines 0, 1, and 2 on PIO instance 0
 *  - DMA channels (2, by claim mechanism)
 *  - 153.6 kBytes of RAM (for pixel color data)
 */

#include "vga16_graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/divider.h"
#include "pico/multicore.h"
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hardware/clocks.h"
#include "hardware/pll.h"
#include "pt_cornell_rp2040_v1_3.h"
#include "colors.h"
#include "drawsprites.h"
#include "drawtile.h"
#include "drawscreen.h"
#include "leveldata.h"
#include "initstructs.h"
#include "movementphysics.h"

// Screen resolution for our VGA output
#define SCREEN_W       640
#define SCREEN_H       480
#define GROUND_TILE_W   30
#define GROUND_TILE_H   30

// Button pins (wire each button to GND when pressed)
#define LEFT_BUTTON_PIN   10
#define RIGHT_BUTTON_PIN  12

float global_x = 340.0f;
Character mario;


int main() {
    stdio_init_all();
    initVGA();
    initLevel();    // populate level[][] from template

    // Spawn Mario
    character_init(&mario, 50.0f, 418.0f);

    // Initialize buttons as inputs with pull-ups
    gpio_init(LEFT_BUTTON_PIN);
    gpio_set_dir(LEFT_BUTTON_PIN, GPIO_IN);
    gpio_pull_up(LEFT_BUTTON_PIN);

    gpio_init(RIGHT_BUTTON_PIN);
    gpio_set_dir(RIGHT_BUTTON_PIN, GPIO_IN);
    gpio_pull_up(RIGHT_BUTTON_PIN);

    while (true) {
        // Read buttons (active low)
        bool leftPressed  = !gpio_get(LEFT_BUTTON_PIN);
        bool rightPressed = !gpio_get(RIGHT_BUTTON_PIN);
        bool jumpPressed  = false;    // no jump yet

        // Update Mario physics
        physics_update_character(&mario, leftPressed, rightPressed, jumpPressed);

        // Clear screen & draw level
        fillRect(0, 0, SCREEN_W, SCREEN_H, OB);
        drawLevel(global_x);

        // Draw Mario
        drawMarioBase(mario.global_x, mario.global_y);

        // Frame timing / yield
        tight_loop_contents();
    }

    return 0;
}
