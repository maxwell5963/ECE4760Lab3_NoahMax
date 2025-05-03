/*───────────────────────────────────────────────────────────────
  drawscreen.h  — new declarations for viewport globals
────────────────────────────────────────────────────────────────*/
#ifndef DRAWSCREEN_H
#define DRAWSCREEN_H

#include <stdint.h>
#include "pico/stdlib.h"
#include "vga16_graphics.h"
#include "leveldata.h"
#include "drawtile.h"

/* geometry */
#define SCREEN_WIDTH   640
#define SCREEN_HEIGHT  480
#define TILE_W         30
#define TILE_H         30
#define COL_SKY        0   /* palette index for sky blue */

/* visible‑column indices (set each time drawLevel/clearscreen runs) */
extern int viewport_start_col;   /* inclusive */
extern int viewport_end_col;     /* exclusive */

/* API */
void clearscreen(float global_x);
void drawLevel(float global_x);

#endif /* DRAWSCREEN_H */
