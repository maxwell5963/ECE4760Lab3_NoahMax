/* movementphysics.c — block‑handling + single coin‑pop + sprite animation
 *
 *  • Adds left/right walk‑cycle animation: when the player holds ← or →,
 *    Mario alternates between the two “run” frames for that direction.
 *  • The animation flips every 4 frames (change ANIM_PERIOD to taste).
 *  • When idle he shows the corresponding base sprite (facing the last
 *    direction moved).
 */

 #include "movementphysics.h"
 #include "initstructs.h"
 #include "colors.h"
 #include "drawsprites.h"   /* sprite draw fns */
 #include "leveldata.h"
 #include "drawscreen.h"
 #include "gamestates.h"
 
 extern float world_x;

 Character mario;

 Goomba goomba1;
 Goomba goomba2;
 Goomba goomba3;
 Goomba goomba4;
 Goomba goomba5;
 Goomba goomba6;
 Goomba goomba7;
 Goomba goomba8;

 
 /* ─── tunables ─────────────────────────────────────────────────────────── */
 #define GRAVITY           4.0f
 #define MAX_FALL_SPEED   20.0f
 #define JUMP_VELOCITY    30.0f
 #define GOOMBA_VELOCITY   2.0f
 
 #define CHAR_W            30
 #define CHAR_H            32
 #define TILE_W            30
 #define TILE_H            30
 #define GOOMBA_W          30
 #define GOOMBA_H          30
 #define GOOMBA_ANIM_PERIOD 8 
 
 /* ─── coin entity (unchanged) ──────────────────────────────────────────── */
 #define COIN_INIT_VY   (-12.0f)
 #define COIN_GRAVITY     1.0f
 #define COIN_LIFETIME   20          /* frames */

 float SPEED_X = 8.0f;
 
 Coin coin = {0};

 bool game_over = false;

 bool spawn_goomba1 = false;
 bool spawn_goomba2 = false;
 bool spawn_goomba3 = false;
 bool spawn_goomba4 = false;
 bool spawn_goomba5 = false;
 bool spawn_goomba6 = false;
 bool spawn_goomba7 = false;
 bool spawn_goomba8 = false;
 
 static void spawn_coin(int row, int col)
 {
     float gx = col * TILE_W + (TILE_W - COIN_W) / 2.0f;
     float gy = row * TILE_H - COIN_H;
     coin_init(&coin, gx, gy, COIN_INIT_VY, COIN_LIFETIME);
 }
 
 static void update_coin(void)
 {
     if (!coin.alive) return;

     if (coin.life == COIN_LIFETIME) {
        coins++;
        score += 10;
     }
 
     /* erase old */
     int old_sx = coin.local_x;
     if (old_sx > -COIN_W && old_sx < 480)
         fillRect(old_sx, coin.local_y, COIN_W, COIN_H, OB);
 
     /* physics step */
     coin.global_y += coin.vel_y;
     coin.vel_y    += COIN_GRAVITY;
     coin.life--;
 
     /* draw */
     coin.local_x = (int)(coin.global_x - (world_x - 640 * 0.5f));
     coin.local_y = (int)coin.global_y;
     int sx = coin.local_x, sy = coin.local_y;
     if (sx > -COIN_W && sx < 480)
         drawCoinSprite(sx, sy);
 
     /* despawn */
     if (coin.life <= 0) {
         if (sx > -COIN_W && sx < 480)
             fillRect(sx, sy, COIN_W, COIN_H, OB);
         coin_collect(&coin);
     }
 }
 
 /* ─── helpers ───────────────────────────────────────────────────────────── */
 static inline bool tile_is_solid(int row, int col)
 {
     if (row < 0 || row >= NUM_ROWS)  return false;
     if (col < 0 || col >= NUM_COLS)  return false;
     return level[row][col] != TILE_EMPTY;
 }
 
 static void handle_block_hit(int row, int col)
 {
     char *tile = &level[row][col];

     float leftWorldX = world_x - (640 * 0.5f);
     short x = col * TILE_W - (int)leftWorldX;
     short y = row * TILE_H;
 
     switch (*tile) {
     case TILE_BRICK:
         *tile = TILE_EMPTY;
         fillRect(x, y, TILE_W, TILE_H, OB);
         break;
     case TILE_QBLOCK:
         *tile = TILE_DEACTIVATED_QBLOCK;
         if (coin.alive) {
            coin.alive = false;
            int sx = coin.local_x, sy = coin.local_y;
            fillRect(sx, sy, COIN_W, COIN_H, OB);
         }
         spawn_coin(row, col);
         drawMysteryBox2(x,y);
         break;
     case TILE_COIN:
         *tile = TILE_EMPTY;
         break;
     default:
         break;
     }
 }
 
 /* bottom collision */
 static bool collides_bottom(const Character *c, float nextY)
 {
     int row   = (int)(nextY + CHAR_H - 1) / TILE_H;
     int col_l = (int)(c->global_x + 6) / TILE_W;
     int col_r = (int)(c->global_x + CHAR_W - 4) / TILE_W;
     return tile_is_solid(row, col_l) || tile_is_solid(row, col_r);
 }
 
 /* ceiling */
 static bool collides_top(const Character *c, float nextY)
 {
     int row   = (int)(nextY - 1) / TILE_H;
     int col_l = (int)(c->global_x + 6) / TILE_W;
     int col_r = (int)(c->global_x + CHAR_W - 4) / TILE_W;
     return tile_is_solid(row, col_l) || tile_is_solid(row, col_r);
 }
 
 /* left & right walls (right probe 5‑px tighter) */
 static bool collides_left(const Character *c, float nextGX)
 {
     int col   = (int)(nextGX + 6) / TILE_W;
     int row_t = (int)(c->local_y - 1) / TILE_H;
     int row_b = (int)(c->local_y + CHAR_H - 1) / TILE_H;
     return tile_is_solid(row_t, col) || tile_is_solid(row_b, col);
 }
 static bool collides_right(const Character *c, float nextGX)
 {
     int col   = (int)(nextGX + CHAR_W - 4) / TILE_W;
     int row_t = (int)(c->local_y - 1) / TILE_H;
     int row_b = (int)(c->local_y + CHAR_H - 1) / TILE_H;
     return tile_is_solid(row_t, col) || tile_is_solid(row_b, col);
 }
 
 /* ─── animation state ──────────────────────────────────────────────────── */
 #define ANIM_PERIOD 8          /* frames per half‑step (lower = faster) */
 static int  anim_counter  = 0; /* global frame tick for walk cycle      */
 static bool facing_right  = true;
 
 static void draw_mario(int sx, int sy, bool moving)
 {
     if (moving) {
         /* choose frame based on anim_counter */
         bool phase = (anim_counter / ANIM_PERIOD) & 1;
         if (facing_right) {
             if (phase)
                 drawMarioRunRight(sx, sy);
             else
                 drawMarioMidStrideRight(sx, sy);
         } else {
             if (phase)
                 drawMarioRunLeft(sx, sy);
             else
                 drawMarioMidStrideLeft(sx, sy);
         }
         anim_counter++;  /* advance only while moving */
     } else {
         /* idle */
         if (facing_right)
             drawMarioBaseRight(sx, sy);
         else
             drawMarioBaseLeft(sx, sy);
         anim_counter = 0; /* reset so walk starts on first frame */
     }
 }

 static bool goomba_collides_bottom(const Goomba *g, float nextY) {
    int row=(int)(nextY+CHAR_H-1)/TILE_H;
    int cl=(int)(g->global_x+6)/TILE_W, cr=(int)(g->global_x+CHAR_W-4)/TILE_W;
    return tile_is_solid(row,cl)||tile_is_solid(row,cr);
}
static bool goomba_collides_left(const Goomba *g, float nextGX) {
    int col=(int)(nextGX+6)/TILE_W;
    int rt=(int)(g->local_y-1)/TILE_H, rb=(int)(g->local_y+CHAR_H-1)/TILE_H;
    return tile_is_solid(rt,col)||tile_is_solid(rb,col);
}
static bool goomba_collides_right(const Goomba *g, float nextGX) {
    int col=(int)(nextGX+CHAR_W-4)/TILE_W;
    int rt=(int)(g->local_y-1)/TILE_H, rb=(int)(g->local_y+CHAR_H-1)/TILE_H;
    return tile_is_solid(rt,col)||tile_is_solid(rb,col);
}

/* one shared counter to flip Goomba frames */
static int goomba_anim_counter = 0;

/**
 * Update one Goomba’s physics + sprite (alternating frames).
 */
void physics_update_goomba(Goomba *g) {
    if (!g || !g->alive) return;

    // erase old
    fillRect(g->local_x, g->local_y, CHAR_W, CHAR_H, OB);

    // horizontal + bounce
    float nx = g->global_x + g->vel_x;
    bool blocked = (g->vel_x<0)
                   ? goomba_collides_left(g,nx)
                   : goomba_collides_right(g,nx);
    if (!blocked) {
        g->global_x = nx;
    } else {
        g->vel_x = -g->vel_x;
    }

    // gravity
    g->vel_y += GRAVITY;
    if (g->vel_y>MAX_FALL_SPEED) g->vel_y = MAX_FALL_SPEED;

    // vertical + floor collision
    float ny = g->global_y + g->vel_y;
    if (!goomba_collides_bottom(g,ny)) {
        g->global_y = ny;
    } else {
        int row = (int)(ny+CHAR_H-1)/TILE_H;
        g->global_y = row*TILE_H - CHAR_H;
        g->vel_y = 0;
    }

    // update screen coords
    g->local_x = (int)(g->global_x - (world_x - 640*0.5f));
    g->local_y = (int)g->global_y;

    // choose frame
    if (g->local_x > -GOOMBA_W) {
        bool phase = (goomba_anim_counter / GOOMBA_ANIM_PERIOD) & 1;
        if (phase) {
            drawGoombaFrame1(g->local_x, g->local_y);
        } else {
            drawGoombaFrame2(g->local_x, g->local_y);
        }
        goomba_anim_counter++;
    }
}

/**
 * Update all Goombas.
 */
void physics_update_goombas(void) {
    physics_update_goomba(&goomba1);
    physics_update_goomba(&goomba2);
    physics_update_goomba(&goomba3);
    physics_update_goomba(&goomba4);
    physics_update_goomba(&goomba5);
    physics_update_goomba(&goomba6);
    physics_update_goomba(&goomba7);
    physics_update_goomba(&goomba8);
}
 
 /* ─── main update ──────────────────────────────────────────────────────── */
 void physics_update_character(Character *c,
                               bool leftPressed,
                               bool rightPressed,
                               bool jumpPressed)
 {
     if (!c) return;
 
     /* erase old sprite */
     fillRect(c->local_x, c->local_y, CHAR_W, CHAR_H, OB);
 
     /* ── horizontal ── */
     bool moving_horiz = leftPressed ^ rightPressed;
     if (moving_horiz) {
         float dx      = leftPressed ? -SPEED_X : SPEED_X;
         float nextGX  = c->global_x + dx;
         bool  blocked = (dx < 0) ? collides_left(c, nextGX) : collides_right(c, nextGX);
 
         if (!blocked) {
             if (leftPressed) {
                 facing_right = false;
                 if (c->local_x + dx >= 0) {
                     c->local_x += dx;
                     c->global_x += dx;
                 }
             } else { /* right */
                 facing_right = true;
                 if (c->local_x + dx <= 300) {
                     c->local_x += dx;
                 } else {
                     clearscreen(world_x);
                     world_x += dx;
                     if (world_x >= 600) {
                        if (!goomba1.alive && !spawn_goomba1) {
                            goomba_init(&goomba1, goomba1.global_x = world_x + 320, 418.0f,  GOOMBA_VELOCITY);
                            goomba1.alive = true;
                            spawn_goomba1 = true;
                     }
                     if (world_x >= 1090) {
                        if (!goomba2.alive && !spawn_goomba2) {
                            goomba_init(&goomba2, goomba2.global_x = world_x + 320, 420.0f,  GOOMBA_VELOCITY);
                            goomba2.alive = true;
                            spawn_goomba2 = true;
                     }
                    }
                    if (world_x >= 1240) {
                        if (!goomba3.alive && !spawn_goomba3) {
                            goomba_init(&goomba3, goomba3.global_x = world_x + 320, 420.0f,  GOOMBA_VELOCITY);
                            goomba3.alive = true;
                            spawn_goomba3 = true;
                     }
                    }
                    if (world_x >= 2200) {
                        if (!goomba4.alive && !spawn_goomba4) {
                            goomba_init(&goomba4, goomba4.global_x = world_x + 320, 420.0f,  GOOMBA_VELOCITY);
                            goomba4.alive = true;
                            spawn_goomba4 = true;
                     }
                    }
                    if (world_x >= 2400) {
                        if (!goomba5.alive && !spawn_goomba5) {
                            goomba_init(&goomba5, goomba5.global_x = world_x + 320, 420.0f,  GOOMBA_VELOCITY);
                            goomba5.alive = true;
                            spawn_goomba5 = true;
                     }
                    }
                 }
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

     if (c->local_y + JUMP_VELOCITY - GRAVITY <= 90) {
        c->local_y = 70;
        c->vel_y = 0.0f;
     }

     if (c->local_y + c->vel_y - GRAVITY >= 445) {
        game_over = true;
     }
 
     /* ── gravity ── */
     c->vel_y += GRAVITY;
     if (c->vel_y > MAX_FALL_SPEED) c->vel_y = MAX_FALL_SPEED;
 
     /* ── vertical ── */
     float nextY = c->local_y + c->vel_y;
 
     if (c->vel_y < 0) {
         /* ascending */
         if (!collides_top(c, nextY)) {
             c->local_y = nextY;
         } else {
             int row   = (int)(nextY - 1) / TILE_H;
             int col_l = (int)(c->global_x) / TILE_W;
             int col_r = (int)(c->global_x + CHAR_W - 1) / TILE_W;
             int col_m = (int)((c->global_x + CHAR_W/2) / TILE_W);
 
             bool left_solid  = tile_is_solid(row, col_l);
             bool right_solid = tile_is_solid(row, col_r);
 
             if (left_solid && right_solid) {
                 if (tile_is_solid(row, col_m))
                     handle_block_hit(row, col_m);
             } else if (left_solid ^ right_solid) {
                 handle_block_hit(row, left_solid ? col_l : col_r);
             }
 
             c->local_y = (row + 1) * TILE_H;
             c->vel_y   = GRAVITY;
         }
         c->on_ground = false;
 
     } else {
         /* descending */
         if (!collides_bottom(c, nextY)) {
             c->local_y   = nextY;
             c->on_ground = false;
         } else {
             int row    = (int)(nextY + CHAR_H + 1) / TILE_H;
             c->local_y = row * TILE_H - CHAR_H;
             c->vel_y   = 0;
             c->on_ground = true;
         }
     }

     drawLevel(world_x);

     physics_update_goombas();

// Replace your Mario-vs-Goomba block with:
{
    Goomba *gs[8] = {
        &goomba1, &goomba2, &goomba3, &goomba4,
        &goomba5, &goomba6, &goomba7, &goomba8
    };
    for (int i = 0; i < 8; i++) {
        Goomba *g = gs[i];
        if (!g->alive) continue;

        bool overlapX = (c->local_x + CHAR_W > g->local_x)
        && (c->local_x           < g->local_x + GOOMBA_W);
        bool overlapY = (c->local_y + CHAR_H > g->local_y)
        && (c->local_y           < g->local_y + GOOMBA_H);


        if (overlapX && overlapY) {
            float penetration = (c->local_y + CHAR_H) - g->local_y;
            if (c->vel_y > 0 && penetration < (CHAR_H / 2)) {
                score += 20;
                // stomp Goomba
                g->alive = false;
                fillRect(g->local_x, g->local_y, GOOMBA_W, GOOMBA_H, OB);
                c->vel_y = -JUMP_VELOCITY * 0.5f;
            } else {
                // side hit → game over
                game_over = true;
            }
        }
    }
}

 
     /* ── draw sprite ── */
     draw_mario(c->local_x, c->local_y, moving_horiz);
 
     /* update coin */
     update_coin();


 }
 