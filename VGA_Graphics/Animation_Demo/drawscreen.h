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

/* main API
 *  playerX_world  – player’s horizontal position in pixels
 */
void drawLevel(void);

#endif /* DRAWSCREEN_H */
