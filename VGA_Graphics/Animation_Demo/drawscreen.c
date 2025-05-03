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
