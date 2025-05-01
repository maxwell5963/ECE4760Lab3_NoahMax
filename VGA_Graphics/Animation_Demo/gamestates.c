
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
#include "controls.h"
#include "initstructs.h"
#include "movementphysics.h"
#include "gamestates.h"

unsigned short score = 0;
unsigned short timer = 0;
unsigned short coins = 0;

void init_game() {
    score = 0; timer = 300; coins = 0;
    fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLUE);
    drawStatusBar(score, timer, coins);
}