#ifndef MOVEMENTPHYSICS_H
#define MOVEMENTPHYSICS_H

#include <stdbool.h>
#include "initstructs.h"

#ifdef __cplusplus
extern "C" {
#endif

// Shared world offset
extern float world_x;
// Shared game-over flag
extern bool game_over;

extern bool spawn_goomba1;
extern bool spawn_goomba2;
extern bool spawn_goomba3;
extern bool spawn_goomba4;
extern bool spawn_goomba5;
extern bool spawn_goomba6;
extern bool spawn_goomba7;
extern bool spawn_goomba8;

extern Character mario;
// Goomba instances
extern Goomba goomba1;
extern Goomba goomba2;
extern Goomba goomba3;
extern Goomba goomba4;
extern Goomba goomba5;
extern Goomba goomba6;
extern Goomba goomba7;
extern Goomba goomba8;

extern Coin coin;
extern float SPEED_X;

/**
 * Update Mario physics and render
 */
void physics_update_character(Character *c,
                              bool leftPressed,
                              bool rightPressed,
                              bool jumpPressed);
/**
 * Update one Goomba's physics and render
 */
void physics_update_goomba(Goomba *g);
/**
 * Update all Goomba instances
 */
void physics_update_goombas(void);

#ifdef __cplusplus
}
#endif

#endif /* MOVEMENTPHYSICS_H */
