#ifndef INITSTRUCTS_H
#define INITSTRUCTS_H

#include <stdbool.h>

/*──────────────────── entity structures ───────────────────*/

/* Mario / player ------------------------------------------------------------*/
typedef struct {
    float global_x;
    float global_y;
    float vel_x;
    float vel_y;
    int   local_x;
    int   local_y;
    bool  on_ground;
} Character;

/* Goomba enemy --------------------------------------------------------------*/
typedef struct {
    float global_x;
    float global_y;
    float vel_x;
    float vel_y;      /* current vertical speed (+down, ‑up)          */
    int   local_x;
    int   local_y;
    bool  alive;
} Goomba;

/* Coin that pops out of a ?‑block -------------------------------------------*/
typedef struct {
    float global_x;
    float global_y;
    float vel_y;      /* current vertical speed (+down, ‑up)          */
    int   local_x;
    int   local_y;
    int   life;       /* frames left before auto‑despawn              */
    bool  alive;
} Coin;

/*──────────────────── creation / destruction ──────────────*/
/* Character */
void character_init(Character *c, float spawnX, float spawnY);
void character_deactivate(Character *c);

/* Goomba */
void goomba_init(Goomba *g, float spawnX, float spawnY, float velX);
void goomba_deactivate(Goomba *g);

/* Coin */
void coin_init(Coin *coin, float posX, float posY, float initVy, int lifetime);
void coin_collect(Coin *coin);   /* mark as picked‑up / despawn        */

#endif /* INITSTRUCTS_H */