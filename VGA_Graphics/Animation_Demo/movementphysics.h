// movementphysics.h
#ifndef MOVEMENTPHYSICS_H
#define MOVEMENTPHYSICS_H

#include <stdbool.h>
#include "initstructs.h"

#ifdef __cplusplus
extern "C" {
#endif

// Declare, don't define
extern float world_x;

<<<<<<< Updated upstream
=======
// Shared game-over flag
extern bool game_over;

extern Character mario;

extern Coin coin;

>>>>>>> Stashed changes
void physics_update_character(Character *c,
                              bool leftPressed,
                              bool rightPressed,
                              bool jumpPressed);

#ifdef __cplusplus
}
#endif

#endif /* MOVEMENTPHYSICS_H */
