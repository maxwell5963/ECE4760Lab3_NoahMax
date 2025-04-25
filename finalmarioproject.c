#include "vga16_graphics.h"
#include "pico/stdlib.h"
#include "pt_cornell_rp2040_v1_3.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/timer.h"
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hardware/clocks.h"
#include "hardware/pll.h"
// And whichever header defines fix15 and the int2fix15/fix2int15 macros



// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9

// Our own defines
#define INITIAL_TIME 300
#define MARIO_W       16
#define MARIO_H       32
#define GOOMBA_W      16
#define GOOMBA_H      16
#define WORLD_BOTTOM  480

static fix15 mario_x, mario_y, mario_vx, mario_vy;
static fix15 goomba_x, goomba_y, goomba_vx;
static bool  goombaAlive = true;

// simple game state
//static int score = 0;
//static int lives = 3;

//Initializing variables for new game 
static unsigned int score = 0; 
static unsigned int lives = 0;
static unsigned int coin_count = 0;
//float time_remaining = 0;
volatile int32_t time_remaining = INITIAL_TIME;  // e.g. #define INITIAL_TIME 400

void initGame(){
    lives = 3;
    time_remaining = INITIAL_TIME;

}

void resetLevel(){
    //put mario's position back to the beginning here 
    //regenerate magic boxes
    //regenerate goombas
    //but dont reset coins, lives, or score
}

// ------------------------------------------------------------------
// spawn/reset routines
// ------------------------------------------------------------------
void spawnMario() {
    mario_x  = int2fix15(50);
    mario_y  = int2fix15(400);
    mario_vx = 0;
    mario_vy = 0;
}

void spawnGoomba() {
    goomba_x  = int2fix15(300);
    goomba_y  = int2fix15(400);
    goomba_vx = int2fix15(1);
    goombaAlive = true;
}

// ------------------------------------------------------------------
// collision & physics updates
// ------------------------------------------------------------------
void updatePhysics() {
    // gravity on Mario
    mario_vy += int2fix15(1);

    // simple horizontal walk for Mario and Goomba
    mario_x += mario_vx;
    mario_y += mario_vy;
    if (goombaAlive)
        goomba_x += goomba_vx;
}

void checkFallOut() {
    if (fix2int15(mario_y) > WORLD_BOTTOM) {
        lives--;
        spawnMario();
    }
}

void checkCollision() {
    // axis-aligned overlap?
    if (!goombaAlive) return;
    bool hit = 
      mario_x <  goomba_x + int2fix15(GOOMBA_W)    &&
      mario_x + int2fix15(MARIO_W) > goomba_x      &&
      mario_y <  goomba_y + int2fix15(GOOMBA_H)    &&
      mario_y + int2fix15(MARIO_H) > goomba_y;

    if (!hit) return;

    // stomp if Mario's feet overlap Goomba's head by only a few pixels
    fix15 overlap = (mario_y + int2fix15(MARIO_H)) - goomba_y;
    if (overlap < int2fix15(5)) {
        // stomp
        score += 100;
        goombaAlive = false;
        // bounce Mario up
        mario_vy = -int2fix15(6);
    } else {
        // Mario runs into Goomba → lose a life
        lives--;
        spawnMario();
    }
}

#define HUD_MARGIN_X   8    // pixels in from the left/right edge
#define HUD_MARGIN_Y   8    // pixels down from the top edge

void drawHud() {
    char buf[64];

    // 1) Score at top‐left
    snprintf(buf, sizeof(buf), "SCORE:%05d", score);
    vga_draw_text(HUD_MARGIN_X, HUD_MARGIN_Y, buf, WHITE);

    // 2) Coins or lives just to the right of the score
    snprintf(buf, sizeof(buf), "LIVES:%d", lives);
    // assume each character is ~8px wide; score text is ~11 chars
    vga_draw_text(HUD_MARGIN_X + 11*8 + 16, HUD_MARGIN_Y, buf, WHITE);

    // 3) Time at top‐right
    snprintf(buf, sizeof(buf), "TIME:%03d", (int)time_remaining);
    // measure approximate text width (6 chars × 8px = 48px)
    vga_draw_text(640 - HUD_MARGIN_X - 6*8, HUD_MARGIN_Y, buf, WHITE);
}


// ------------------------------------------------------------------
// Replace your protothread_anim with this simplified Mario thread
// ------------------------------------------------------------------
static PT_THREAD(protothread_mario(struct pt *pt)) {
    PT_BEGIN(pt);

    // frame‑timing vars
    static int begin, spare;

    // initial spawn
    spawnMario();
    spawnGoomba();

    while (1) {
        begin = time_us_32();

        // erase previous sprites
        drawRect(fix2int15(mario_x),
                 fix2int15(mario_y),
                 MARIO_W, MARIO_H,
                 BLACK);
        if (goombaAlive)
            drawRect(fix2int15(goomba_x),
                     fix2int15(goomba_y),
                     GOOMBA_W, GOOMBA_H,
                     BLACK);

        // update world
        updatePhysics();
        checkFallOut();
        checkCollision();

        // draw sprites
        drawRect(fix2int15(mario_x),
                 fix2int15(mario_y),
                 MARIO_W, MARIO_H,
                 WHITE);
        if (goombaAlive)
            drawRect(fix2int15(goomba_x),
                     fix2int15(goomba_y),
                     GOOMBA_W, GOOMBA_H,
                     RED);

        // draw the scoreboard
        drawHud();

        // maintain constant frame rate
        spare = FRAME_RATE - (time_us_32() - begin);
        PT_YIELD_usec(spare);
    }

    PT_END(pt);
}