#include "movementphysics.h"
#include <math.h>
#include "pico/stdlib.h"
#include "vga16_graphics.h"

/*──────── timing & geometry (sync with main) ────────*/
#define FPS             60.0f
#define NUM_ROWS        16
#define NUM_COLS        600
#define TILE_W          30
#define TILE_H          30
#define CHAR_W          30
#define CHAR_H          60

/*──────── tuned physics constants ─────────*/
#define MAX_SPEED_X     (240.0f / FPS)
#define ACCEL_X         (MAX_SPEED_X / 20.0f)
#define FRICTION_X      (MAX_SPEED_X / 20.0f)
#define GRAVITY         (30.0f / FPS)
#define JUMP_VELOCITY   10.0f
#define MAX_FALL_SPEED  (900.0f / FPS)

/* Level map supplied by your main program */
extern char level[NUM_COLS][NUM_ROWS];

/*──────── collision helpers ────────*/
static inline bool is_solid(int col, int row)
{
    if (col < 0 || col >= NUM_COLS) return false;
    if (row < 0 || row >= NUM_ROWS) return false;
    return level[col][row] != ' ';
}

static bool collides_left (const Character *c, float nextX)
{
    int col = (int)nextX / TILE_W;
    int r1  = (int) c->global_y               / TILE_H;
    int r2  = (int)(c->global_y + CHAR_H - 1) / TILE_H;
    return is_solid(col, r1) || is_solid(col, r2);
}

static bool collides_right(const Character *c, float nextX)
{
    int col = (int)(nextX + CHAR_W - 1) / TILE_W;
    int r1  = (int) c->global_y               / TILE_H;
    int r2  = (int)(c->global_y + CHAR_H - 1) / TILE_H;
    return is_solid(col, r1) || is_solid(col, r2);
}

static bool collides_top(const Character *c, float nextY)
{
    int row = (int)nextY / TILE_H;
    int c1  = (int) c->global_x              / TILE_W;
    int c2  = (int)(c->global_x + CHAR_W - 1) / TILE_W;
    return is_solid(c1, row) || is_solid(c2, row);
}

static bool collides_bottom(const Character *c, float nextY)
{
    int row = (int)(nextY + CHAR_H - 1) / TILE_H;
    int c1  = (int) c->global_x              / TILE_W;
    int c2  = (int)(c->global_x + CHAR_W - 1) / TILE_W;
    return is_solid(c1, row) || is_solid(c2, row);
}

/*──────── vertical movement helper ────────*/
static void move_vertical(Character *c, float newY)
{
    if (c->vel_y > 0.0f) {         /* falling */
        if (!collides_bottom(c, newY)) {
            c->global_y  = newY;
            c->on_ground = false;
        } else {
            int row      = ((int)c->global_y + CHAR_H) / TILE_H;
            c->global_y  = row * TILE_H - CHAR_H;
            c->vel_y     = 0.0f;
            c->on_ground = true;
        }
    } else if (c->vel_y < 0.0f) {  /* rising */
        if (!collides_top(c, newY)) {
            c->global_y = newY;
        } else {
            c->vel_y = 0.0f;       /* head-bump */
        }
    }
}

/*──────── public update function ────────*/
void physics_update_character(Character *c,
                              bool leftPressed,
                              bool rightPressed,
                              bool jumpPressed)
{
    static bool prevJump = false;
    if (!c) return;

    /* horizontal accel / friction */
    int dir = 0;
    if (leftPressed ^ rightPressed)
        dir = leftPressed ? -1 : 1;

    if (dir < 0)
        c->vel_x = fmaxf(c->vel_x - ACCEL_X, -MAX_SPEED_X);
    else if (dir > 0)
        c->vel_x = fminf(c->vel_x + ACCEL_X,  MAX_SPEED_X);
    else {
        if (c->vel_x > 0.0f)
            c->vel_x = fmaxf(c->vel_x - FRICTION_X, 0.0f);
        else if (c->vel_x < 0.0f)
            c->vel_x = fminf(c->vel_x + FRICTION_X, 0.0f);
    }

    /* horizontal movement & collision */
    float nextX = c->global_x + c->vel_x;
    if (c->vel_x < 0.0f) {
        if (!collides_left(c, nextX)) c->global_x = nextX;
        else                          c->vel_x = 0.0f;
    } else if (c->vel_x > 0.0f) {
        if (!collides_right(c, nextX)) c->global_x = nextX;
        else                           c->vel_x = 0.0f;
    }

    if (c->global_x < 0.0f) {
        c->global_x = 0.0f;
        c->vel_x    = 0.0f;
    }

    /* jump */
    if (jumpPressed && !prevJump && c->on_ground) {
        c->vel_y     = -JUMP_VELOCITY;
        c->on_ground = false;
    }
    prevJump = jumpPressed;

    /* gravity */
    c->vel_y += GRAVITY;
    if (c->vel_y > MAX_FALL_SPEED)
        c->vel_y = MAX_FALL_SPEED;

    move_vertical(c, c->global_y + c->vel_y);
}