// movementphysics.c
#include "movementphysics.h"

/*──────── simple horizontal speed ────────*/
#define SPEED_X  (2.0f)   // pixels per frame

void physics_update_character(Character *c,
                              bool leftPressed,
                              bool rightPressed,
                              bool jumpPressed) {
    if (!c) return;

    // Move left or right at fixed speed
    if (leftPressed && !rightPressed) {
        c->global_x -= SPEED_X;
    } else if (rightPressed && !leftPressed) {
        c->global_x += SPEED_X;
    }

    // Prevent going off‐screen on the left
    if (c->global_x < 0.0f) {
        c->global_x = 0.0f;
    }

    // (Optional) clamp on the right side if you know your level width:
    // float maxX = NUM_COLS * TILE_W - CHAR_W;
    // if (c->global_x > maxX) c->global_x = maxX;
}
