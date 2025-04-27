
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
 *
 */

// Include the VGA grahics library
#include "vga16_graphics.h"
// Include standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// Include Pico libraries
#include "pico/stdlib.h"
#include "pico/divider.h"
#include "pico/multicore.h"
// Include hardware libraries
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hardware/clocks.h"
#include "hardware/pll.h"
// Include protothreads
#include "pt_cornell_rp2040_v1_3.h"
#include "colors.h"
#include "drawsprites.h"
#include "drawtile.h"
#include "drawscreen.h"
#include "leveldata.h"

// Screen resolution for our VGA output
#define SCREEN_W 640
#define SCREEN_H 480
#define GROUND_TILE_W 30
#define GROUND_TILE_H 30

#if 0
int main() {
    // Initialize standard I/O (for debug over USB UART, if needed)
    stdio_init_all();

    // Initialize VGA output (sets up PIO, DMA, etc.)
    initVGA();

    // Fill the entire screen with a light-blue background
    // (Assumes LIGHT_BLUE is defined in colors.h)
    fillRect(0, 0, SCREEN_W, SCREEN_H, OB);
    // Draw a few sprites at arbitrary positions for PoC
    drawGoombaFrame1( 50,  50);   // Goomba in top -left
    drawGoombaDead(50, 150);
    drawGoombaFrame2(50, 100);
    drawMarioBase(200, 100);   // Mario more to the right
    drawCoinSprite(350,  75);   // Coin up and right
    drawFloatyBrick(50, 100);
    drawMysteryBox(50, 150);
    drawMysteryBox2(50, 200);
        // draw a full row of ground tiles along the bottom
        for(int x = -10; x < SCREEN_W; x += GROUND_TILE_W) {
          // place each tile so its bottom edge == screen bottom
          drawGroundTile(x, SCREEN_H - GROUND_TILE_H);
      }


    // Keep the display static
    while (true) {
        // tight loop to avoid exiting main
        tight_loop_contents();
    }

    return 0;
}

#endif

int main() {
  stdio_init_all();
  initVGA();

  initLevel();    // populate level[][] from template
  fillRect(0,0,SCREEN_W,SCREEN_H, OB);  // clear background
  drawLevel();    // draw every tile

  while (true) {
      tight_loop_contents();
  }
  return 0;
}