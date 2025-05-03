/*******************************************************************************
 * leveldata.h
 *
 * Authors: Max Warner (mtw82), Noah Wilson (njw66)
 *
 * Description:
 *   Level data and tile definitions for the game world in our ECE 4760 Final
 *   Project, a Super Mario Bros–inspired game. Provides tile codes, map
 *   dimensions, and initialization for the level layout.
 *
 ******************************************************************************/

#ifndef LEVELDATA_H
#define LEVELDATA_H

/* Map dimensions */
#define NUM_ROWS 16      /* top-to-bottom */
#define NUM_COLS 82     /* left-to-right */

/* Tile codes */
#define TILE_EMPTY  ' '
#define TILE_GROUND '#'
#define TILE_BRICK  'B'
#define TILE_QBLOCK '?'
#define TILE_DEACTIVATED_QBLOCK  'D'
#define TILE_STAIR  'S'
#define TILE_PIPE   'P'
#define TILE_COIN   'C'
#define TILE_ENEMY  'G'
#define TILE_FLAG   'F'

/* Global tile map: level[row][col] */
extern char level[NUM_ROWS][NUM_COLS];
void initLevel(void);

#endif /* LEVELDATA_H */
