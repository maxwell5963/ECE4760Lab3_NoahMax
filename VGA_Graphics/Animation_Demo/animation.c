
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
#include "gamestates.h"

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
    const short START_Y   = 100;
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

static struct pt pt_timer;    // your Protothread control block
static uint32_t last_ms;      // track last “second‐tick” timestamp

//--------------------------------------------------------------------------------
// This is the Protothread that drives the countdown.
//--------------------------------------------------------------------------------
PT_THREAD(timer_thread(struct pt *pt))
{
    PT_BEGIN(pt);

    // stamp the start time
    last_ms = to_ms_since_boot(get_absolute_time());

    while (1) {
        // wait until 1000ms have elapsed
        PT_WAIT_UNTIL(pt,
            (to_ms_since_boot(get_absolute_time()) - last_ms) >= 1000);

        last_ms += 1000;    // bump our “last” forward by one second

        if (timer > 0) {
            --timer;
        }
        fillRect(335, 20, 80, 50, BLUE);
        // once timer hits zero it just stays there
    }

    PT_END(pt);
}

//--------------------------------------------------------------------------------
// Test thread for Mario animation
//--------------------------------------------------------------------------------
PT_THREAD(mario_proto(struct pt *pt))
{
    PT_BEGIN(pt);

    // stamp the start time
    last_ms = to_ms_since_boot(get_absolute_time());

    while (1) {
        // wait until 1000ms have elapsed
        PT_WAIT_UNTIL(pt,
            (to_ms_since_boot(get_absolute_time()) - last_ms) >= 1000);

        last_ms += 1000;    // bump our “last” forward by one second

        if (timer > 0) {
            --timer;
        }
        fillRect(335, 20, 80, 50, BLUE);
        // once timer hits zero it just stays there
    }

    PT_END(pt);
}

#define MARIO_X            170    // change as needed
#define MARIO_Y            140
#define ANIM_INTERVAL_MS   200     // frame flip every 200 ms

static struct pt pt_mario;
static uint32_t last_anim_ms;
static bool     mario_toggle;

PT_THREAD(mario_anim_thread(struct pt *pt))
{
    PT_BEGIN(pt);

    // initialize our timestamp and toggle
    last_anim_ms = to_ms_since_boot(get_absolute_time());
    mario_toggle = false;

    while (1) {
        // wait until it's time for the next frame
        PT_WAIT_UNTIL(pt,
            (to_ms_since_boot(get_absolute_time()) - last_anim_ms)
               >= ANIM_INTERVAL_MS);

        last_anim_ms += ANIM_INTERVAL_MS;

        // erase the old sprite
        fillRect(MARIO_X, MARIO_Y, 30, 32, BLUE);

        // draw the next frame
        if (mario_toggle) {
            drawMarioRun1(MARIO_X, MARIO_Y);
        } else {
            drawMarioMidStride(MARIO_X, MARIO_Y);
        }
        mario_toggle = !mario_toggle;
    }

    PT_END(pt);
}

#define GOOMBA_X           170       // adjust to where you want it
#define GOOMBA_Y           100
#define GOOMBA_INTERVAL_MS 300       // flip every 300 ms
#define GOOMBA_SIZE        30        // as defined in sprites.h

static struct pt pt_goomba;
static uint32_t    last_goomba_ms;
static bool        goomba_toggle;

PT_THREAD(goomba_anim_thread(struct pt *pt))
{
    PT_BEGIN(pt);

    last_goomba_ms = to_ms_since_boot(get_absolute_time());
    goomba_toggle  = false;

    while (1) {
        PT_WAIT_UNTIL(pt,
            (to_ms_since_boot(get_absolute_time()) - last_goomba_ms)
              >= GOOMBA_INTERVAL_MS);

        last_goomba_ms += GOOMBA_INTERVAL_MS;

        // erase old Goomba
        fillRect(GOOMBA_X, GOOMBA_Y, GOOMBA_SIZE, GOOMBA_SIZE, BLUE);

        // draw next frame
        if (goomba_toggle) {
            drawGoombaFrame1(GOOMBA_X, GOOMBA_Y);
        } else {
            drawGoombaFrame2(GOOMBA_X, GOOMBA_Y);
        }
        goomba_toggle = !goomba_toggle;
    }

    PT_END(pt);
}

int main() {
    stdio_init_all();
    initVGA();
    init_game(); 
    drawTestPalette();

    while (1) {
        // let the timer thread run a little bit
        timer_thread(&pt_timer);
        mario_anim_thread(&pt_mario);
        goomba_anim_thread(&pt_goomba);
        // now update the display
        drawStatusBar(score, timer, coins);
    }
  
}



