
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

  #define FRAME_RATE_US   (1000000/60)  // ~16.7 ms/frame
  #define DB_THRESH       2             // # frames for debounce
  #define RUN_THRESH      6             // # frames between run-frame toggles
  
  static PT_THREAD(protothread_mario(struct pt *pt))
  {
      PT_BEGIN(pt);
  
      // --- per-thread state ---
      static Character mario;
      static bool deb_left = false, deb_right = false, deb_jump = false;
      static uint8_t db_left = 0, db_right = 0, db_jump = 0;
      static bool run_frame = false;
      static uint8_t run_count = 0;
      static int begin_time, spare_time;
  
      // one-time init
      controls_init();
      character_init(&mario,
                     /* spawnX */  0.0f,
                     /* spawnY */ (TILE_H + MARIO_H));
      // note: choose spawnY so Mario sits on ground :contentReference[oaicite:8]{index=8}&#8203;:contentReference[oaicite:9]{index=9}
  
      while(1) {
          begin_time = time_us_32() ;
  
          //   — debounce LEFT —
          bool rawL = left_pressed();
          if(rawL == deb_left) {
              db_left = 0;
          } else if(++db_left >= DB_THRESH) {
              deb_left = rawL;
              db_left  = 0;
          }
          //   — debounce RIGHT —
          bool rawR = right_pressed();
          if(rawR == deb_right) {
              db_right = 0;
          } else if(++db_right >= DB_THRESH) {
              deb_right = rawR;
              db_right  = 0;
          }
          //   — debounce JUMP —
          bool rawJ = jump_pressed();
          if(rawJ == deb_jump) {
              db_jump = 0;
          } else if(++db_jump >= DB_THRESH) {
              deb_jump = rawJ;
              db_jump  = 0;
          }
  
          //   — physics update —
          physics_update_character(&mario,
                                   deb_left,
                                   deb_right,
                                   deb_jump);
  
          //   — redraw entire scene —
          //fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COL_SKY);
          drawLevel(mario.global_x);
  
          //   — choose sprite —
          if ((deb_left ^ deb_right) && mario.on_ground) {
              // running on ground: toggle every RUN_THRESH frames
              if (++run_count >= RUN_THRESH) {
                  run_frame = !run_frame;
                  run_count = 0;
              }
              if (run_frame)
                  drawMarioRun1(mario.local_x, mario.local_y);
              else
                  drawMarioMidStride(mario.local_x, mario.local_y);
          } else {
              // idle OR in the air
              drawMarioBase(mario.local_x, mario.local_y);
          }
  
          //   — frame timing yield —
          spare_time = FRAME_RATE_US - (time_us_32() - begin_time);
          PT_YIELD_usec(spare_time);
      }
  
      PT_END(pt);
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

static struct pt pt_mario;

int main() {
    stdio_init_all();
    initVGA();
    PT_INIT(&pt_mario);

    while (1) {
      drawTestPalette();
      protothread_mario(&pt_mario);

    }
}



