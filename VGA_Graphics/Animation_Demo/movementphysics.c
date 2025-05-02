/* movementphysics.c  — hover‑free version */

#include "movementphysics.h"
#include "colors.h"
#include "drawsprites.h"
#include "leveldata.h"

/* tunables ------------------------------------------------ */
#define SPEED_X         8.0f
#define GRAVITY         1.2f
#define MAX_FALL_SPEED  12.0f
#define JUMP_VELOCITY   18.0f

#define CHAR_W          30
#define CHAR_H          32
#define TILE_W          30
#define TILE_H          30

/* helpers ------------------------------------------------- */
static inline bool is_solid(int row, int x_l, int x_r)
{
    int col_l = x_l / TILE_W;
    int col_r = x_r / TILE_W;
    return (level[row][col_l] != ' ') || (level[row][col_r] != ' ');
}

/* true if the *next* Y position would collide with ground */
static bool collides_bottom(const Character *c, float nextY)
{
    int row      = (int)(nextY + CHAR_H + 1) / TILE_H;   /* tile under feet */
    int x_l      = c->global_x;
    int x_r      = c->global_x + CHAR_W - 5;
    return is_solid(row, x_l, x_r);
}

/* -------------------------------------------------------- */
void physics_update_character(Character *c,
                              bool leftPressed,
                              bool rightPressed,
                              bool jumpPressed)
{
    if (!c) return;

    /* erase old sprite */
    fillRect(c->local_x, c->local_y, CHAR_W, CHAR_H, OB);

    /* ── horizontal ── */
    if (leftPressed ^ rightPressed) {
        float dx = (leftPressed ? -SPEED_X : SPEED_X);

        if (leftPressed && c->local_x > 0.0f) {
            c->local_x += dx;
            c->global_x += dx;
        } else if (rightPressed) {
            if (c->local_x + SPEED_X <= 300.0f) {
                c->local_x += dx;
                c->global_x += dx;
            } else {          /* scroll */
                c->global_x += dx;
                world_x     += dx;
            }
        }
    }

    /* ── jump ── */
    if (jumpPressed && c->on_ground) {
        c->vel_y     = -JUMP_VELOCITY;
        c->on_ground = false;
    }

    /* ── gravity ── */
    c->vel_y += GRAVITY;
    if (c->vel_y > MAX_FALL_SPEED) c->vel_y = MAX_FALL_SPEED;

    /* ── vertical ── */
    float nextY = c->local_y + c->vel_y;

    if (c->vel_y < 0.0f) {          /* ascending */
        c->local_y  = nextY;
        c->on_ground = false;
    } else {                        /* descending */
        if (!collides_bottom(c, nextY)) {
            c->local_y  = nextY;
            c->on_ground = false;
        } else {
            /* snap precisely to tile top → no hover */
            int row      = (int)(nextY + CHAR_H + 1) / TILE_H;
            c->local_y   = row * TILE_H - CHAR_H;
            c->vel_y     = 0.0f;
            c->on_ground = true;
        }
    }

    /* draw new sprite */
    drawMarioBase(c->local_x, c->local_y);
}
