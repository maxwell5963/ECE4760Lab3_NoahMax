// movementphysics.h
#ifndef MOVEMENTPHYSICS_H
#define MOVEMENTPHYSICS_H

#include <stdbool.h>
#include "initstructs.h"   /* brings in Character */

#ifdef __cplusplus
extern "C" {
#endif

/* Per-frame physics update for Mario */
void physics_update_character(Character *c,
                              bool leftPressed,
                              bool rightPressed,
                              bool jumpPressed);

#ifdef __cplusplus
}
#endif

#endif /* MOVEMENTPHYSICS_H */
