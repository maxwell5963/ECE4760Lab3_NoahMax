
/**
 * Hunter Adams (vha3@cornell.edu)
 * 
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
#include "controls.h"
#include "initstructs.h"
#include "movementphysics.h"

// Screen resolution for our VGA output
#define SCREEN_W 640
#define SCREEN_H 480
#define TILE_SIZE 30

static Character mario;

float thingymajiggy = 340.0f;
/// Animate a single goomba “swap” at (x,y)
void animateGoombaShiftAndFlip(short start_x, short y, char bg_color) {
  short x = start_x;
  while (true) {
      // Frame 1
      drawGoombaFrame1(x, y);
      sleep_ms(500);

      // Erase
      fillRect(x, y, TILE_SIZE, TILE_SIZE, bg_color);

      // Frame 2
      drawGoombaFrame2(x, y);
      sleep_ms(500);

      // Erase
      fillRect(x, y, TILE_SIZE, TILE_SIZE, bg_color);
  }
}


int main() {
  stdio_init_all();
  initVGA();
  initLevel();    // populate level[][] from template
  character_init(&mario, 310.0f, 415.0f);
  while (true) {
    fillRect(0,0,SCREEN_W,SCREEN_H, BLUE);  // clear background
    drawLevel(thingymajiggy);    // draw every tile
    //drawGoombaFrame1( 50,  50);   // Goomba in top -left
    //drawGoombaFrame2(50, 100);
    drawGoombaDead(50, 150);
    drawMarioBase(mario.local_x, mario.local_y);   // Mario more to the right
    drawCoinSprite(350,  75);   // Coin up and right
    drawMarioRun1(250, 100);


    // Frame 1
    drawGoombaFrame1(50, 50);
    sleep_ms(500);

    // Erase
    fillRect(50, 50, TILE_SIZE, TILE_SIZE, OB);

    // Frame 2
    drawGoombaFrame2(50, 50);
    sleep_ms(500);

    // Erase
    fillRect(50, 50, TILE_SIZE, TILE_SIZE, OB);

    // Shift right
    //x += 20;
    //if (x > SCREEN_W - TILE_SIZE) {
        // wrap around
        //x = 0;

}
  while (true) {
      tight_loop_contents();
  }
  return 0;
}



// main function to draw the test palette
void drawTestPalette(void) {
    const short START_X   = 10;
    const short START_Y   = 10;
    const short SPACING_X = 40;   // horizontal gap between items
    const short SPACING_Y = 40;   // vertical gap between rows
  
    short x = START_X;
    short y = START_Y;
  
    fillRect(0, 0, SCREEN_W, SCREEN_H, BLUE);
  
    // — Row 0: Goomba anim frames
    drawGoombaFrame1(          x,            y);        x += SPACING_X;
    drawGoombaFrame2(          x,            y);        x += SPACING_X;
    drawGoombaDead(            x,            y+14);        x += SPACING_X;
    drawGoombaDeadFlipped(     x,            y+14);        x += SPACING_X;

  
    // — Row 1: Coin + Mario
    y += SPACING_Y;
    x  = START_X;
    drawCoinSprite(            x,            y);        x += SPACING_X;
    drawMarioBase(             x,            y);        x += SPACING_X;
    drawMarioRun1(             x,            y);        x += SPACING_X;
    drawMarioMidStride(        x,            y);        x += SPACING_X;


    // — Row 2: Tiles
    y += SPACING_Y;
    x  = START_X;
    drawGroundTile(            x,            y);        x += TILE_SIZE + 5;
    drawStairTile(             x,            y);        x += TILE_SIZE + 5;
    drawFloatyBrick(           x,            y);        x += TILE_SIZE + 5;
    drawMysteryBox(            x,            y);        x += TILE_SIZE + 5;
    drawMysteryBox2(           x,            y);        x += TILE_SIZE + 5;

    drawPipeTopLeft(  x, y); x += TILE_SIZE + 5;
    drawPipeTopRight( x, y); x += TILE_SIZE + 5;
    drawPipeBotLeft(  x, y); x += TILE_SIZE + 5;
    drawPipeBotRight( x, y);

    // draw a full row of ground tiles along the bottom
    for(int x = -10; x < SCREEN_W; x += TILE_SIZE) {
      // place each tile so its bottom edge == screen bottom
      drawGroundTile(x, SCREEN_H - TILE_SIZE);
    }


    //NOTE FROM MAX: Anything animation-related must go at end due to the infinite while-loop
    //otherwise it'll never get to it 
    //animateGoombaShiftAndFlip(180, 10, BLUE); 

  }


#if 0
int main() {
    // Initialize standard I/O (for debug over USB UART, if needed)
    stdio_init_all();

    // Initialize VGA output (sets up PIO, DMA, etc.)
    initVGA();
    drawTestPalette();

    // Keep the display static
    while (true) {
      if (reset_pressed()) {
          // clear screen to blue
          fillRect(0, 0, SCREEN_W, SCREEN_H, LB);  
      }
      tight_loop_contents();
    }

    return 0;
}

#endif


