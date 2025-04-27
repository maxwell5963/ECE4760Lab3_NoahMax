//=== tiles.h =============================================================
// Authors: Max Warner (mtw82), Noah Wilson (njw82)
// Description:
//    Tile dimensions, extern declarations and draw-function prototypes
//    for the Super Mario–style project.
//=========================================================================

#ifndef DRAWTILES_H
#define DRAWTILES_H

#include <stdint.h>

//─── tile dimensions ──────────────────────────────────────────────────────
#define TILE_SIZE 30

// tile declarations
extern const uint16_t ground_tile[TILE_SIZE][TILE_SIZE];
extern const uint16_t stair_tile[TILE_SIZE][TILE_SIZE];
extern const uint16_t floaty_brick[TILE_SIZE][TILE_SIZE];
extern const uint16_t mystery_box[TILE_SIZE][TILE_SIZE];
extern const uint16_t mystery_box_frame2[TILE_SIZE][TILE_SIZE];
extern const uint16_t pipe_top_left[TILE_SIZE][TILE_SIZE];
extern const uint16_t pipe_top_right[TILE_SIZE][TILE_SIZE];
extern const uint16_t pipe_bot_left[TILE_SIZE][TILE_SIZE];
extern const uint16_t pipe_bot_right[TILE_SIZE][TILE_SIZE];

// draw function declarations

void DrawTile(short x0, short y0, const uint16_t *tile);

void drawGroundTile(short x, short y);
void drawStairTile(short x, short y);
void drawFloatyBrick(short x, short y);
void drawMysteryBox(short x, short y);
void drawMysteryBox2(short x, short y);

void drawPipeTopLeft(short x, short y);
void drawPipeTopRight(short x, short y);
void drawPipeBotLeft(short x, short y);
void drawPipeBotRight(short x, short y);


#endif  // DRAWTILES_H