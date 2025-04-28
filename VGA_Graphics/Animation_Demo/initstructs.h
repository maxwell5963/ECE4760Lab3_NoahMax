#ifndef INITSTRUCTS_H
#define INITSTRUCTS_H

#include <stdbool.h>

/*──────────────────── entity structures ───────────────────*/

typedef struct {
    float global_x;
    float global_y;
    float vel_x;
    float vel_y;
    int   local_x;
    int   local_y;
    bool  on_ground;
} Character;

typedef struct {
    float global_x;
    float global_y;
    float vel_x;
    int   local_x;
    int   local_y;
    bool  alive;
} Goomba;

typedef struct {
    float global_x;
    float global_y;
    int   local_x;
    int   local_y;
    bool  alive;
} Coin;

/*──────────────────── creation / destruction ──────────────*/

void character_init(Character *c, float spawnX, float spawnY);
void character_deactivate(Character *c);

void goomba_init(Goomba *g, float spawnX, float spawnY, float velX);
void goomba_deactivate(Goomba *g);

void coin_init(Coin *coin, float posX, float posY);
void coin_collect(Coin *coin);

#endif /* INITSTRUCTS_H */
