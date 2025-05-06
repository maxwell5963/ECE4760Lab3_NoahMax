
// Include the VGA grahics library
#include "vga16_graphics.h"
// Include standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// Include Pico libraries
#include "pico/stdlib.h"
#include "pico/divider.h"
#include "pico/multicore.h"
// Include hardware libraries
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hardware/clocks.h"
#include "hardware/pll.h"
// Include protothreads
#include "colors.h"
#include "drawsprites.h"
#include "drawtile.h"
#include "drawscreen.h"
#include "leveldata.h"
#include "initstructs.h"
#include "movementphysics.h"
#include "gamestates.h"
#include "movementphysics.h"

// globally defined variables for score, time, and coins 
// these can be modified at will in animation.c 
unsigned short score =  0;
unsigned short timerr = 0;
unsigned short coins =  0;

// temporary storage variables to keep track 
// of when to update the scoreboard (instead of constantly updating)
unsigned short prev_coins  = 0;
unsigned short prev_score  = 0;
unsigned short prev_timerr = 0;

void init_game() {
    score = 0; timerr = 999; coins = 0; prev_coins = coins; prev_score = score; prev_timerr = timerr;
    fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, OB);
    initLevel();
    character_init(&mario, 50.0f, 418.0f);
    initStatusBar(score, coins);
}

void reset_game() {
    return;
}