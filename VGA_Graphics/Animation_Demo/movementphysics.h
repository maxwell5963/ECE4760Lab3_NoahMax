#ifndef MOVEMENTPHYSICS_H
#define MOVEMENTPHYSICS_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declaration coming from your game header */
typedef struct Character Character;

/**
 * @brief Initialise physics‑specific state for a Character.
 *
 * Resets velocity and state flags; does not touch position so you can
 * place the character wherever you like before calling it.
 */
void physics_init_character(Character *c);

/**
 * @brief Per‑frame physics update for the main character (Mario).
 *
 * Handles horizontal acceleration / friction, jump initiation, gravity and
 * collision with the tile map so that Mario never falls through the floor or
 * passes through solid blocks.
 *
 * Call once every frame (e.g. 60 Hz) *before* rendering and pass in the raw
 * button states you read from the GPIO pins (active‑high booleans).
 *
 * @param c            Pointer to the character instance to update.
 * @param leftPressed  True while LEFT button is pressed.
 * @param rightPressed True while RIGHT button is pressed.
 * @param jumpPressed  True while JUMP button is pressed.
 */
void physics_update_character(Character *c,
                              bool leftPressed,
                              bool rightPressed,
                              bool jumpPressed);

#ifdef __cplusplus
}
#endif

#endif /* MOVEMENTPHYSICS_H */
