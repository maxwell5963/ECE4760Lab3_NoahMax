/*******************************************************************************
 * drawscreen.h
 *
 * Authors: Max Warner (mtw82), Noah Wilson (njw66)
 *
 * Description:
 *   Screen-drawing API for rendering the game world based on the player’s
 *   position. Handles level scrolling and tile rendering for our ECE 4760
 *   Final Project, a Super Mario Bros–inspired game.
 *
 ******************************************************************************/

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
void drawLevel(float global_x);
void drawStatusBar(unsigned short score, unsigned short timer, unsigned short coins);

#endif /* DRAWSCREEN_H */
