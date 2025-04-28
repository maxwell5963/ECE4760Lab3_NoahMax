#include "initstructs.h"
#include <stddef.h>

/*──────────────────── helper ───────────────────────────────*/
static inline int fx_to_int(float v) { return (int)v; }

/*──────────────────── Character ────────────────────────────*/
void character_init(Character *c, float spawnX, float spawnY)
{
    if (!c) return;
    c->global_x  = spawnX;
    c->global_y  = spawnY;
    c->vel_x     = 0.0f;
    c->vel_y     = 0.0f;
    c->local_x   = fx_to_int(spawnX);
    c->local_y   = fx_to_int(spawnY);
    c->on_ground = false;
}

void character_deactivate(Character *c)
{
    if (!c) return;
    /* Move off‑screen & disable physics */
    c->global_x = -1000.0f;
    c->global_y = -1000.0f;
    c->vel_x    = 0.0f;
    c->vel_y    = 0.0f;
    c->on_ground = false;
}

/*──────────────────── Goomba ───────────────────────────────*/
void goomba_init(Goomba *g, float spawnX, float spawnY, float velX)
{
    if (!g) return;
    g->global_x  = spawnX;
    g->global_y  = spawnY;
    g->vel_x     = velX;
    g->local_x   = fx_to_int(spawnX);
    g->local_y   = fx_to_int(spawnY);
    g->alive     = true;
}

void goomba_deactivate(Goomba *g)
{
    if (!g) return;
    g->alive = false;
}

/*──────────────────── Coin ─────────────────────────────────*/
void coin_init(Coin *coin, float globalX, float globalY)
{
    if (!coin) return;
    coin->global_x = globalX;
    coin->global_y = globalY;
    coin->local_x  = fx_to_int(globalX);
    coin->local_y  = fx_to_int(globalY);
    coin->alive    = true;
}

void coin_deactivate(Coin *coin)
{
    if (!coin) return;
    coin->alive = false;
}
