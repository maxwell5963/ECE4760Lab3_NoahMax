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

#include "colors.h"
#include "drawsprites.h"
#include "drawtile.h"
#include "drawscreen.h"
#include "leveldata.h"
#include "initstructs.h"
#include "movementphysics.h"

#define GAME_STARTED
#define GAME_RESET
#define GAME_OVER

extern unsigned short score; // score 
extern unsigned short timerr; // time (seconds)
extern unsigned short coins; // coins collected

extern unsigned short prev_score;
extern unsigned short prev_coins;
extern unsigned short prev_timerr;

void init_game();
void reset_game();