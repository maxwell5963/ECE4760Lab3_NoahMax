// drawscreen.h

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

void clearscreen(float global_x);
void drawLevel(float global_x);
void initStatusBar(unsigned short score, unsigned short coins);
void drawGameOver(unsigned short score, 
                  unsigned short coins); 

void updateStatusBar(unsigned short c, unsigned short s);
void writeCoins(unsigned short coins);
void writeScore(unsigned short score);
void writeTimer(unsigned short time);


#endif /* DRAWSCREEN_H */
