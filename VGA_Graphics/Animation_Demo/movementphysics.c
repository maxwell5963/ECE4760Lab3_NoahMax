#include "movementphysics.h"
#include <math.h>
#include "pico/stdlib.h"
#include "vga16_graphics.h"   /* only for drawPixel helper if needed */

/*──────────────────── timing & geometry (mirrors main) ───────────────────*/
#define FPS             60.0f
#define NUM_ROWS        16
#define NUM_COLS        600
#define TILE_W          30
#define TILE_H          30
#define CHAR_W          30
#define CHAR_H          60

/*──────────────────── physics parameters ───────────────────────────────*/
#define MAX_SPEED_X     (240.0f / FPS)
#define ACCEL_X         (MAX_SPEED_X / 20.0f)
#define FRICTION_X      (MAX_SPEED_X / 20.0f)
#define GRAVITY         (30.0f / FPS)
#define JUMP_VELOCITY   10.0f
#define MAX_FALL_SPEED  (900.0f / FPS)

/*──────────────────── extern level data (from level file) ──────────────*/
extern char level[NUM_COLS][NUM_ROWS];

/*──────────────────── Character definition (mirrors main) ───────────────*/
struct Character {
    float pos_x;
    float pos_y;
    float vel_x;
    float vel_y;
    int   local_x;
    int   local_y;
    bool  on_ground;
};

/*──────────────────── internal helpers ─────────────────────────────────*/
static inline bool is_solid(int col, int row)
{
    if (col < 0 || col >= NUM_COLS) return false;
    if (row < 0 || row >= NUM_ROWS) return false;
    return (level[col][row] != ' ');
}

static bool collides_left(const struct Character *c, float nextX)
{
    int col = (int)(nextX) / TILE_W;
    int r1  = (int)(c->pos_y) / TILE_H;
    int r2  = (int)(c->pos_y + CHAR_H - 1) / TILE_H;
    return is_solid(col, r1) || is_solid(col, r2);
}

static bool collides_right(const struct Character *c, float nextX)
{
    int col = (int)(nextX + CHAR_W - 1) / TILE_W;
    int r1  = (int)(c->pos_y) / TILE_H;
    int r2  = (int)(c->pos_y + CHAR_H - 1) / TILE_H;
    return is_solid(col, r1) || is_solid(col, r2);
}

static bool collides_top(const struct Character *c, float nextY)
{
    int row = (int)(nextY) / TILE_H;
    int c1  = (int)(c->pos_x) / TILE_W;
    int c2  = (int)(c->pos_x + CHAR_W - 1) / TILE_W;
    return is_solid(c1, row) || is_solid(c2, row);
}

static bool collides_bottom(const struct Character *c, float nextY)
{
    int row = (int)(nextY + CHAR_H - 1) / TILE_H;
    int c1  = (int)(c->pos_x) / TILE_W;
    int c2  = (int)(c->pos_x + CHAR_W - 1) / TILE_W;
    return is_solid(c1, row) || is_solid(c2, row);
}

/* Break / coin block activation is handled elsewhere; only stop movement. */

static void move_vertical(struct Character *c, float newY)
{
    if (c->vel_y > 0.0f) {
        /* Falling */
        if (!collides_bottom(c, newY)) {
            c->pos_y = newY;
            c->on_ground = false;
        } else {
            int row = ((int)c->pos_y + CHAR_H) / TILE_H;
            c->pos_y = row * TILE_H - CHAR_H;
            c->vel_y = 0.0f;
            c->on_ground = true;
        }
    } else if (c->vel_y < 0.0f) {
        /* Rising */
        if (!collides_top(c, newY)) {
            c->pos_y = newY;
        } else {
            c->vel_y = 0.0f; /* Head bump – vertical velocity cancelled */
        }
    }
}

/*──────────────────── public API ───────────────────────────────────────*/
void physics_init_character(struct Character *c)
{
    if (!c) return;
    c->vel_x = 0.0f;
    c->vel_y = 0.0f;
    c->on_ground = false;
}

void physics_update_character(struct Character *c,
                              bool leftPressed,
                              bool rightPressed,
                              bool jumpPressed)
{
    static bool prevLeft = false;
    static bool prevRight = false;

    if (!c) return;

    /*──────────────── horizontal input locking ───────────────*/
    int horizLock = 0;
    if (leftPressed && rightPressed) {
        if (!prevLeft && !prevRight) {
            /* new simultaneous press – keep last direction */
            horizLock = 0;
        }
    } else if (leftPressed) {
        horizLock = -1;
    } else if (rightPressed) {
        horizLock = 1;
    }

    prevLeft  = leftPressed;
    prevRight = rightPressed;

    /*──────────────── apply acceleration / friction ──────────*/
    if (horizLock < 0) {
        c->vel_x = fmaxf(c->vel_x - ACCEL_X, -MAX_SPEED_X);
    } else if (horizLock > 0) {
        c->vel_x = fminf(c->vel_x + ACCEL_X,  MAX_SPEED_X);
    } else {
        /* friction */
        if (c->vel_x > 0.0f) {
            c->vel_x = fmaxf(c->vel_x - FRICTION_X, 0.0f);
        } else if (c->vel_x < 0.0f) {
            c->vel_x = fminf(c->vel_x + FRICTION_X, 0.0f);
        }
    }

    /*──────────────── horizontal movement & collision ────────*/
    float nextX = c->pos_x + c->vel_x;

    if (c->vel_x < 0.0f) {
        if (!collides_left(c, nextX)) {
            c->pos_x = nextX;
        } else {
            c->vel_x = 0.0f;
        }
    } else if (c->vel_x > 0.0f) {
        if (!collides_right(c, nextX)) {
            c->pos_x = nextX;
        } else {
            c->vel_x = 0.0f;
        }
    }

    if (c->pos_x < 0.0f) {
        c->pos_x = 0.0f;
        c->vel_x = 0.0f;
    }

    /*──────────────── jump initiation ────────────────────────*/
    static bool prevJump = false;
    if (jumpPressed && !prevJump && c->on_ground) {
        c->vel_y = -JUMP_VELOCITY;
        c->on_ground = false;
    }
    prevJump = jumpPressed;

    /*──────────────── gravity & vertical movement ───────────*/
    c->vel_y += GRAVITY;
    if (c->vel_y > MAX_FALL_SPEED) {
        c->vel_y = MAX_FALL_SPEED;
    }

    move_vertical(c, c->pos_y + c->vel_y);
}
