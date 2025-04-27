

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

void drawLevel(float global_x) {
    // TILE_SIZE is 30, as in drawtile.h
    for(int row = 0; row < NUM_ROWS; row++) {
        for(int col = 0; col < NUM_COLS; col++) {
            // convert tile‐coordinates to pixel‐coordinates
            short x = col * TILE_SIZE;
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

