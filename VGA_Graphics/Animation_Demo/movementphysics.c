/* movementphysics.c — block‑handling + single coin‑pop (no MAX_COINS array)
 *
 *  • When Mario bonks a ?‑block we re‑initialise one Coin instance.
 *  • The coin jumps up, slows under gravity, and despawns when its life hits 0.
 *  • If Mario hits another ?‑block while a coin is still alive, the coin is
 *    simply re‑started from the new block position.
 */

 #include "movementphysics.h"
 #include "initstructs.h"
 #include "colors.h"
 #include "drawsprites.h"     /* drawMarioBase(), drawCoin()          */
 #include "leveldata.h"
 #include "drawscreen.h"
 #include "drawsprites.h"
 
 extern float world_x;
 
 /* ─── tunables ─────────────────────────────────────────── */
 #define SPEED_X           8.0f
 #define GRAVITY           3.0f
 #define MAX_FALL_SPEED   20.0f
 #define JUMP_VELOCITY    30.0f
 
 #define CHAR_W           30
 #define CHAR_H           32
 #define TILE_W           30
 #define TILE_H           30
 
 /* ─── single coin entity ───────────────────────────────── */
 #define COIN_INIT_VY   (-12.0f)
 #define COIN_GRAVITY     1.0f
 #define COIN_LIFETIME   20          /* frames */
 
 static Coin coin = {0};             /* the one live coin */
 
 /* spawn / reset coin just above (row,col) tile */
 static void spawn_coin(int row, int col)
 {
     float gx = col * TILE_W + (TILE_W - COIN_W) / 2.0f;
     float gy = row * TILE_H - COIN_H;
     coin_init(&coin, gx, gy, COIN_INIT_VY, COIN_LIFETIME);
 }
 
 /* advance & draw coin (if alive) once per frame */
 static void update_coin(void)
 {
     if (!coin.alive) return;
 
     /* erase old sprite */
     int old_sx = coin.local_x;
     if (old_sx > -COIN_W && old_sx < 480)
         fillRect(old_sx, coin.local_y, COIN_W, COIN_H, OB);
 
     /* physics step */
     coin.global_y += coin.vel_y;
     coin.vel_y    += COIN_GRAVITY;
     coin.life--;
 
     /* project to screen space & draw */
     coin.local_x = (int)(coin.global_x - (world_x - (640 * 0.5f)));
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
 
 /* ─── helpers ─────────────────────────────────────────── */
 static inline bool tile_is_solid(int row, int col)
 {
     if (row < 0 || row >= NUM_ROWS)  return false;
     if (col < 0 || col >= NUM_COLS)  return false;
     return level[row][col] != TILE_EMPTY;
 }
 
 /* What happens when Mario hits a block from below */
 static void handle_block_hit(int row, int col)
 {
     char *tile = &level[row][col];
 
     switch (*tile)
     {
     case TILE_BRICK:
         *tile = TILE_EMPTY;
         fillRect(0, 0, 480, 640, OB);
         drawLevel(world_x);
         break;
 
     case TILE_QBLOCK:
         *tile = TILE_DEACTIVATED_QBLOCK;
         spawn_coin(row, col);        /* ← coin pop */
         clearscreen(world_x);
         drawLevel(world_x);
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
 
 /* ceiling collision */
 static bool collides_top(const Character *c, float nextY)
 {
     int row   = (int)(nextY - 1) / TILE_H;
     int col_l = (int)(c->global_x + 6) / TILE_W;
     int col_r = (int)(c->global_x + CHAR_W - 4) / TILE_W;
     return tile_is_solid(row, col_l) || tile_is_solid(row, col_r);
 }
 
 /*-----------------------------------------------------------------
   Side‑wall collisions
   • Left probe +1 px; Right probe –5 px (tighter)
 ------------------------------------------------------------------*/
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
 
 /* ─── main physics update ─────────────────────────────── */
 void physics_update_character(Character *c,
                               bool leftPressed,
                               bool rightPressed,
                               bool jumpPressed)
 {
     if (!c) return;
 
     /* erase Mario */
     fillRect(c->local_x, c->local_y, CHAR_W, CHAR_H, OB);
 
     /* ── horizontal motion ── */
     if (leftPressed ^ rightPressed) {
         float dx      = leftPressed ? -SPEED_X : SPEED_X;
         float nextGX  = c->global_x + dx;
         bool  blocked = (dx < 0) ? collides_left(c, nextGX)
                                  : collides_right(c, nextGX);
 
         if (!blocked) {
             if (leftPressed) {
                 if (c->local_x + dx >= 0) {
                     c->local_x += dx;
                     c->global_x += dx;
                 }
             } else {                    /* moving right */
                 if (c->local_x + dx <= 300) {
                     c->local_x += dx;
                 } else {
                     clearscreen(world_x);
                     world_x += dx;
                     drawLevel(world_x);
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
 
     if (c->vel_y < 0) {                 /* ascending */
         if (!collides_top(c, nextY)) {
             c->local_y = nextY;
         } else {                         /* bonk! */
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
 
     } else {                             /* descending */
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
 
     /* draw Mario */
     drawMarioBase(c->local_x, c->local_y);
 
     /* update single coin */
     update_coin();
 }
 