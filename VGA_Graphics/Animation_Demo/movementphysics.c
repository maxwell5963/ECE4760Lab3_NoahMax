/* movementphysics.c — full file with “bonk‑and‑fall” ceiling collisions */

#include "movementphysics.h"
#include "colors.h"
#include "drawsprites.h"
#include "leveldata.h"

/* ─── tunables ─────────────────────────────────────────── */
#define SPEED_X         8.0f
#define GRAVITY         1.2f
#define MAX_FALL_SPEED  12.0f
#define JUMP_VELOCITY   18.0f

#define CHAR_W          30
#define CHAR_H          32
#define TILE_W          30
#define TILE_H          30

/* ─── helpers ──────────────────────────────────────────── */
static inline bool tile_is_solid(int row, int col)
{
    if (row < 0 || row >= NUM_ROWS)  return false;
    if (col < 0 || col >= NUM_COLS)  return false;
    return level[row][col] != ' ';
}

/* ground check */
static bool collides_bottom(const Character *c, float nextY)
{
    int row   = (int)(nextY + CHAR_H + 1) / TILE_H;
    int col_l = (int)(c->global_x          ) / TILE_W;
    int col_r = (int)(c->global_x + CHAR_W - 5) / TILE_W;
    return tile_is_solid(row, col_l) || tile_is_solid(row, col_r);
}

/* ceiling check */
static bool collides_top(const Character *c, float nextY)
{
    int row   = (int)(nextY - 1) / TILE_H;            /* tile above head */
    int col_l = (int)(c->global_x          ) / TILE_W;
    int col_r = (int)(c->global_x + CHAR_W - 5) / TILE_W;
    return tile_is_solid(row, col_l) || tile_is_solid(row, col_r);
}

/* side‑wall checks */
static bool collides_left(const Character *c, float nextGlobalX)
{
    int col   = (int)(nextGlobalX - 1) / TILE_W;
    int row_t = (int)(c->local_y            ) / TILE_H;
    int row_b = (int)(c->local_y + CHAR_H - 1) / TILE_H;
    return tile_is_solid(row_t, col) || tile_is_solid(row_b, col);
}

static bool collides_right(const Character *c, float nextGlobalX)
{
    int col   = (int)(nextGlobalX + CHAR_W + 1) / TILE_W;
    int row_t = (int)(c->local_y            ) / TILE_H;
    int row_b = (int)(c->local_y + CHAR_H - 1) / TILE_H;
    return tile_is_solid(row_t, col) || tile_is_solid(row_b, col);
}

/* ─── main physics update ─────────────────────────────── */
void physics_update_character(Character *c,
                              bool leftPressed,
                              bool rightPressed,
                              bool jumpPressed)
{
    if (!c) return;

    /* erase old sprite */
    fillRect(c->local_x, c->local_y, CHAR_W, CHAR_H, OB);

    /* ── horizontal motion ── */
    if (leftPressed ^ rightPressed) {
        float dx          = leftPressed ? -SPEED_X : SPEED_X;
        float nextGlobalX = c->global_x + dx;
        bool blocked      = (dx < 0) ? collides_left(c, nextGlobalX)
                                     : collides_right(c, nextGlobalX);

        if (!blocked) {
            if (leftPressed) {
                if (c->local_x + dx >= 0.0f) {
                    c->local_x += dx;
                    c->global_x += dx;
                }
                // else: do not move or update global_x
            } else { /* rightPressed */
                if (c->local_x + dx <= 300.0f) {
                    c->local_x += dx;
                } else {
                    world_x += dx;
                }
                c->global_x += dx;
            }
        }
    }

    /* ── jumping ── */
    if (jumpPressed && c->on_ground) {
        c->vel_y     = -JUMP_VELOCITY;
        c->on_ground = false;
    }

    /* ── gravity ── */
    c->vel_y += GRAVITY;
    if (c->vel_y > MAX_FALL_SPEED) c->vel_y = MAX_FALL_SPEED;

    /* ── vertical motion ── */
    float nextY = c->local_y + c->vel_y;

    if (c->vel_y < 0.0f) {                       /* ascending */
        if (!collides_top(c, nextY)) {
            c->local_y = nextY;
        } else {                                 /* bonk! */
            int row    = (int)(nextY - 1) / TILE_H;
            c->local_y = (row + 1) * TILE_H;     /* snap just below tile */
            c->vel_y   = GRAVITY;                /* start falling NOW  */
        }
        c->on_ground = false;

    } else {                                     /* descending */
        if (!collides_bottom(c, nextY)) {
            c->local_y = nextY;
            c->on_ground = false;
        } else {                                 /* land */
            int row    = (int)(nextY + CHAR_H + 1) / TILE_H;
            c->local_y = row * TILE_H - CHAR_H;
            c->vel_y   = 0.0f;
            c->on_ground = true;
        }
    }

    /* draw new sprite */
    drawMarioBase(c->local_x, c->local_y);
}
