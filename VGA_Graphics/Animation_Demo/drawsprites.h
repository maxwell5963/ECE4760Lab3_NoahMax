//=== drawsprites.h =============================================================
// Authors: Max Warner (mtw82), Noah Wilson (njw82)
// Description:
//    Sprite dimensions, extern declarations and draw-function prototypes
//    for the Super Mario–style project.
//
//============================================================================

#ifndef DRAWSPRITES_H
#define DRAWSPRITES_H

#include <stdint.h>

//─── sprite dimensions ──────────────────────────────────────────────────────

#define GOOMBA_SIZE     30
#define GOOMBA_DEAD_H   16
#define GOOMBA_DEAD_W   30

#define COIN_H          25
#define COIN_W          15

#define MARIO_H         32
#define MARIO_W         30

//─── extern declarations ────────────────────────────────────────────────────
extern const uint16_t goombaframe1[GOOMBA_SIZE][GOOMBA_SIZE];
extern const uint16_t goombaframe2[GOOMBA_SIZE][GOOMBA_SIZE];
extern const uint16_t goomba_dead[GOOMBA_DEAD_H][GOOMBA_DEAD_W];
extern const uint16_t goomba_dead_flipped[GOOMBA_DEAD_H][GOOMBA_DEAD_W];

extern const uint16_t coin_sprite[COIN_H][COIN_W];
extern const uint16_t mario_base[MARIO_H][MARIO_W];
extern const uint16_t mario_run1[MARIO_H][MARIO_W];

//─── draw-function prototypes ───────────────────────────────────────────────

void DrawSprite(short x0, short y0, const uint16_t *sprite, short w, short h);

void drawGoombaFrame1(short x, short y);
void drawGoombaFrame2(short x, short y);
void drawGoombaDead(short x, short y);
void drawGoombaDeadFlipped(short x, short y);
void drawCoinSprite(short x, short y);
void drawMarioBase(short x, short y);
void drawMarioRun1(short x, short y);


#endif  // DRAWSPRITES_H
