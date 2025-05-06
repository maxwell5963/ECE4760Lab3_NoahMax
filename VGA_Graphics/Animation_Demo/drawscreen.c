/*───────────────────────────────────────────────────────────────
  drawlevel.c  — exposes viewport_start_col & viewport_end_col
────────────────────────────────────────────────────────────────*/

/* Public header */
#include "drawscreen.h"

/* Engine headers */
#include "leveldata.h"
#include "drawtile.h"
#include "drawsprites.h"
#include "colors.h"
<<<<<<< Updated upstream
=======
#include "vga16_graphics.h"
#include "string.h"
#include <stdio.h>
#include "movementphysics.h"
>>>>>>> Stashed changes

/* ─── GLOBALS (now visible to other .c files) ──────────────── */
int viewport_start_col = 0;   /* first tile column currently visible  */
int viewport_end_col   = 0;   /* one‑past‑last visible tile column    */

/* ─── helpers ──────────────────────────────────────────────── */
static inline void clamp_left_world(float *leftWorldX)
{
    const int levelWidthPx = NUM_COLS * TILE_W;

    if (*leftWorldX < 0)
        *leftWorldX = 0;
    else if (*leftWorldX > levelWidthPx - SCREEN_WIDTH)
        *leftWorldX = levelWidthPx - SCREEN_WIDTH;
}

/* ─────────────────────────────────────────────────────────────
   Draw the background tiles that are currently on screen
   (Mario’s global_x is the camera centre).
 ─────────────────────────────────────────────────────────────*/
void drawLevel(float global_x)
{
    /* find left edge of viewport in world space */
    float leftWorldX = global_x - (SCREEN_WIDTH * 0.5f);
    clamp_left_world(&leftWorldX);

    /* update globals so other modules can query them */
    viewport_start_col = (int)(leftWorldX / TILE_W);
    viewport_end_col   = (int)((leftWorldX + SCREEN_WIDTH) / TILE_W) + 1;
    if (viewport_end_col > NUM_COLS) viewport_end_col = NUM_COLS;

    /* render only the visible tiles */
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = viewport_start_col; col < viewport_end_col; col++) {

            /* convert tile coords → screen pixels */
            short x = col * TILE_W - (int)leftWorldX;
            short y = row * TILE_H;

            switch (level[row][col]) {
            case TILE_GROUND:             drawGroundTile   (x, y); break;
            case TILE_BRICK:              drawFloatyBrick  (x, y); break;
            case TILE_QBLOCK:             drawMysteryBox   (x, y); break;
            case TILE_DEACTIVATED_QBLOCK: drawMysteryBox2  (x, y); break;
            case TILE_FLAG:
            case TILE_EMPTY:
            default: /* nothing */                        break;
            }
        }
    }
}

/* ─────────────────────────────────────────────────────────────
   Quick “wipe” that fills every visible tile with sky colour.
 ─────────────────────────────────────────────────────────────*/
void clearscreen(float global_x)
{
    float leftWorldX = global_x - (SCREEN_WIDTH * 0.5f);
    clamp_left_world(&leftWorldX);

    viewport_start_col = (int)(leftWorldX / TILE_W);
    viewport_end_col   = (int)((leftWorldX + SCREEN_WIDTH) / TILE_W) + 1;
    if (viewport_end_col > NUM_COLS) viewport_end_col = NUM_COLS;

    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = viewport_start_col; col < viewport_end_col; col++) {

            short x = col * TILE_W - (int)leftWorldX;
            short y = row * TILE_H;

            fillRect(x, y, TILE_W, TILE_H, OB);   /* sky‑blue wipe */
        }
    }
}
<<<<<<< Updated upstream
=======


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
    
    coin.alive = false;          // clear coin state
    int old_sx = coin.local_x;
    if (old_sx > -30 && old_sx < 480)
        fillRect(old_sx, coin.local_y, 30, 30, OB);

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
>>>>>>> Stashed changes
