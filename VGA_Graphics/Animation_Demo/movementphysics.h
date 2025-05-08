#ifndef MOVEMENTPHYSICS_H
#define MOVEMENTPHYSICS_H

#include <stdbool.h>
#include "initstructs.h"

#ifdef __cplusplus
extern "C" {
#endif

// Shared world offset
extern float world_x;

#define MAX_GOOMBAS 8

extern Goomba goombas[MAX_GOOMBAS];
void spawn_goomba(int row, int col);

// Shared game-over flag
extern bool game_over;

extern Character mario;

void physics_update_character(Character *c,
                              bool leftPressed,
                              bool rightPressed,
                              bool jumpPressed);

#ifdef __cplusplus
}
 
#endif

#endif /* MOVEMENTPHYSICS_H */
