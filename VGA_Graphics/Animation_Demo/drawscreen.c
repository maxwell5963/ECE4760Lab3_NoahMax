

#if 0
/* Global map stored in leveldata.c (row-major: level[row][col]) */
extern char level[NUM_ROWS][NUM_COLS];

/* ─── solid-fill helper ─── */
static inline void fillRect(int x, int y, int w, int h, uint8_t colour)
{
    for (int yy = y; yy < y + h; ++yy)
        for (int xx = x; xx < x + w; ++xx)
            drawPixel(xx, yy, colour);
}
#endif

/* ──────────────────────────────────────────────────────────────────────────
   Render everything based on the player’s global X position.
   Only rows/columns visible in the viewport are drawn.
   ────────────────────────────────────────────────────────────────────────── */
// drawlevel.c
#include "drawscreen.h"
#include "leveldata.h"
#include "drawtile.h"
#include "drawsprites.h"
#include "colors.h"
#include "vga16_graphics.h"
#include "string.h"
#include <stdio.h>
#include "movementphysics.h"

bool game_over_drawn = false;


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
        for(int col = startCol; col < endCol+1; col++) {   
            // convert tile‐coordinates to pixel‐coordinates
            short x = col * TILE_SIZE - (int)leftWorldX;
            short y = row * TILE_SIZE;

            switch(level[row][col]) {
                case TILE_STAIR:
                    drawStairTile(x,y);
                    break;
                case TILE_GROUND:
                    drawGroundTile(x, y);
                    break;
                case TILE_BRICK:
                    drawFloatyBrick(x, y);
                    break;
                case TILE_QBLOCK:
                    drawMysteryBox(x, y);
                    break;
                case TILE_DEACTIVATED_QBLOCK:
                    drawMysteryBox2(x, y);
                    break;
                case TILE_FLAG_POLE:
                    drawFlagPole(x, y);
                    break;
                case TILE_FLAG:
                    drawFlag(x, y);
                    break;
                case TILE_EMPTY:
                default:
                    // nothing to draw
                    break;
            }
        }
    }
}

void clearscreen(float global_x) {
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

            if (level[row][col] != TILE_EMPTY &&
                level[row][col + 1] == TILE_EMPTY)
            {
                fillRect(x + TILE_SIZE - SPEED_X, y, SPEED_X, TILE_SIZE, OB); // Blue edge marker
            }


        }
    }
}


const int y = 30;  

void initStatusBar(unsigned short score, unsigned short coins) {
int textsize = 3;
int width = 640;

char buf[32];
int x = 70;
                  // vertical position of text
const int margin = 30;               // pixels between fields
const int cw = 6 * textsize;         // character width in pixels (6px font * size)
const int ch = 8 * textsize;         // character height if you ever need it

// clear the top bar
//fillRect(0, 0, width, ch + (y - 0), BLUE);

setTextSize(3);
setTextColor(WT);

// Score
sprintf(buf, "Score:%03u", score);
setCursor(70, y);
writeString(buf);

// Time
sprintf(buf, "Time:%03u");
setCursor(265, y);
writeString(buf);

// Coins
sprintf(buf, "Coins:%u", coins);
setCursor(435, y);
writeString(buf);
}

void drawGameOver(unsigned short score, unsigned short coins) {
    int textsize = 5;
    int width = 640;
    int height = 480;

    char buf[32];
    const int margin = 30;               // pixels between fields
    const int cw = 4 * textsize;         // character width in pixels (6px font * size)
    const int ch = 8 * textsize;         // character height if you ever need it

    setTextSize(5);
    setTextColor(WT);   

    coin.alive = false;

    //First, blank the screen out 
    fillRect(0, 0, width, height, BLACK);

    //Now we draw "GAME OVER"
    sprintf(buf, "GAME OVER");
    setCursor(190,120);
    writeString(buf);

    setTextSize(3);

    int x = 150;
    int y = 300;
    
    // Coins
    sprintf(buf, "Coins:%u", coins);
    setCursor(x, y);
    writeString(buf);
    x += strlen(buf) * cw + margin;
    
    // Score
    sprintf(buf, "Score:%03u", score);
    setCursor(x, y);
    writeString(buf);

    game_over_drawn = true;
}

void writeCoins(unsigned short coin) {
    char buf[32];
    setTextSize(3);
    fillRect(540,30,40,25, OB);
    sprintf(buf, "%02u", coin);
    setCursor(546, y);
    writeString(buf);
}

void writeScore(unsigned short score) {
    char buf[32];
    setTextSize(3);
    fillRect(175, 30, 70, 25, OB);
    setCursor(175,y);
    sprintf(buf, "%03u", score);
    writeString(buf);
}

void writeTimer(unsigned short time) {
    char buf[32];
    fillRect(352, 28, 55, 27, OB);
    setTextSize(3);
    sprintf(buf, "%u", time);
    setCursor(352, y);
    writeString(buf);
}

void updateStatusBar(unsigned short c, unsigned short s) {
    setTextColor(WT); 
    char buf[32];
    sprintf(buf, "Score:");
    setCursor(70, y);
    writeString(buf);
    sprintf(buf, "Time:");
    setCursor(265, y);
    writeString(buf);
    sprintf(buf, "Coins:");
    setCursor(435, y);
    writeString(buf);

    writeCoins(c);
    writeScore(s);
}
