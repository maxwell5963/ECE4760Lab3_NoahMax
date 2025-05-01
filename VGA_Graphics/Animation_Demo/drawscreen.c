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
#include "colors.h"
#include "drawsprites.h"
#include "drawtile.h"
#include "drawscreen.h"
#include "leveldata.h"
#include "controls.h"
#include "initstructs.h"
#include "movementphysics.h"
#include <stdio.h>  // for sprintf

void drawLevel(float global_x) {
    // TILE_SIZE is 30, as in drawtile.h
    float leftWorldX = global_x - (SCREEN_WIDTH * 0.5f);

    /* clamp within level limits */
    const int levelWidthPx = NUM_COLS * TILE_W;
    if (leftWorldX < 0) leftWorldX = 0;
    if (leftWorldX > levelWidthPx - SCREEN_WIDTH)
        leftWorldX = levelWidthPx - SCREEN_WIDTH;

    /* first & last visible tile columns */
    int startCol = (int)(leftWorldX / TILE_W);
    int endCol   = (int)((leftWorldX + SCREEN_WIDTH) / TILE_W) + 1;
    if (endCol > NUM_COLS) endCol = NUM_COLS;

    for(int row = 0; row < NUM_ROWS; row++) {
        for(int col = startCol; col < NUM_COLS; col++) {   
            // convert tile‐coordinates to pixel‐coordinates
            short x = col * TILE_SIZE - (int)leftWorldX;
            short y = row * TILE_SIZE;

            switch(level[row][col]) {
                case TILE_GROUND:
                    drawGroundTile(x, y);
                    break;
                case TILE_BRICK:
                    drawFloatyBrick(x, y);
                    break;
                case TILE_QBLOCK:
                    drawMysteryBox(x, y);
                    break;
                case TILE_FLAG:
                    // you’ll need a drawFlag()...
                    break;
                case TILE_EMPTY:
                default:
                    // nothing to draw
                    break;
            }
        }
    }
}

void drawStatusBar(unsigned short score,
    unsigned short timer,
    unsigned short coins) {
int textsize = 3;
int width = 640;

char buf[32];
int x = 90;
const int y = 30;                    // vertical position of text
const int margin = 30;               // pixels between fields
const int cw = 6 * textsize;         // character width in pixels (6px font * size)
const int ch = 8 * textsize;         // character height if you ever need it

// clear the top bar
//fillRect(0, 0, width, ch + (y - 0), BLUE);

setTextSize(3);
setTextColor(WT);

// Score
sprintf(buf, "Score:%u", score);
setCursor(x, y);
writeString(buf);
x += strlen(buf) * cw + margin;

// Time
sprintf(buf, "Time:%u", timer);
setCursor(x, y);
writeString(buf);
x += strlen(buf) * cw + margin;

// Coins
sprintf(buf, "Coins:%u", coins);
setCursor(x, y);
writeString(buf);
}

