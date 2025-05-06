/*
 * Hunter Adams (vha3@cornell.edu)
 *
 * Mario-style side-scroll demo running on core 1.
 * Core 0 is left free for USB / CLI tasks.
 *
 * HARDWARE CONNECTIONS
 *  - GPIO 16 -> VGA Hsync
 *  - GPIO 17 -> VGA Vsync
 *  - GPIO 18 -> 470 Ω -> VGA Green
 *  - GPIO 19 -> 330 Ω -> VGA Green
 *  - GPIO 20 -> 330 Ω -> VGA Blue
 *  - GPIO 21 -> 330 Ω -> VGA Red
 *  - RP2040 GND -> VGA GND
 *
 * BUTTONS (pulled-up, press to GND)
 *  - GPIO 10 -> Move Left
 *  - GPIO 12 -> Move Right
 *  - GPIO 11 -> Jump
 *
 * RESOURCES USED
 *  - PIO state machines 0,1,2 on PIO instance 0
 *  - DMA channels (2, by claim mechanism)
 *  - 153.6 kB of RAM (pixel buffer)
 *
 * NOTE
 *  Movement physics and scrolling are updated once every
 *  PHYSICS_PERIOD frames instead of every single frame.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <math.h>
 #include <string.h>
 
 #include "pico/stdlib.h"
 #include "pico/divider.h"
 #include "pico/multicore.h"
 
 #include "hardware/pio.h"
 #include "hardware/dma.h"
 #include "hardware/clocks.h"
 #include "hardware/pll.h"
 
 #include "pt_cornell_rp2040_v1_3.h"
 
 #include "vga16_graphics.h"
 #include "colors.h"
 #include "drawsprites.h"
 #include "drawtile.h"
 #include "drawscreen.h"
 #include "leveldata.h"
 #include "initstructs.h"
 #include "movementphysics.h"
 #include "gamestates.h"
 
 /* ─── constants ─────────────────────────────────────────── */
 #define SCREEN_W            640
 #define SCREEN_H            480
 
 /* update physics every PHYSICS_PERIOD frames */
 #define PHYSICS_PERIOD      10     /* only tweak needed */
 
 /* Button pins (pulled-up; short to GND when pressed) */
 #define LEFT_BUTTON_PIN     10
 #define RIGHT_BUTTON_PIN    12
 #define JUMP_BUTTON_PIN     11   /* NEW */
 #define RESET_BUTTON_PIN    13
 
 /* ─── global game state ─────────────────────────────────── */
 float     world_x = 320.0f;
 // bool game_over = false;   // GAME OVER functionality commented out
 
 static struct pt pt_timer;    // your Protothread control block
 static uint32_t last_ms;      // track last “second‐tick” timestamp

 extern bool game_over;
 
 //--------------------------------------------------------------------------------
 // This is the Protothread that drives the countdown.
 //--------------------------------------------------------------------------------
 PT_THREAD(timer_thread(struct pt *pt))
 {
     PT_BEGIN(pt);
 
     // stamp the start time
     last_ms = to_ms_since_boot(get_absolute_time());
 
     while (1) {
         // wait until 1000ms have elapsed
         PT_WAIT_UNTIL(pt,
             (to_ms_since_boot(get_absolute_time()) - last_ms) >= 1000);
 
         last_ms += 1000;    // bump our “last” forward by one second
 
         if (timerr > 0) {
             --timerr;
         }
         // if (timerr == 0) {
         //     game_over = true;  // GAME OVER trigger removed
         // }
         if (!game_over) {  
            fillRect(352, 28, 55, 27, OB);
        }
         // once timer hits zero it just stays there
     }
 
     PT_END(pt);
 }
 
 /* ──────────────────────────────────────────────────────────
    Core 1: complete game loop
    ────────────────────────────────────────────────────────── */
 void core1_main(void)
 {
     /* 1) one-time init */
     initVGA();
     init_game();
     character_init(&mario, 50.0f, 418.0f);
     PT_INIT(&pt_timer);
 
     /* buttons: inputs + pull-ups */
     gpio_init(LEFT_BUTTON_PIN);   gpio_set_dir(LEFT_BUTTON_PIN,  GPIO_IN);  gpio_pull_up(LEFT_BUTTON_PIN);
     gpio_init(RIGHT_BUTTON_PIN);  gpio_set_dir(RIGHT_BUTTON_PIN, GPIO_IN);  gpio_pull_up(RIGHT_BUTTON_PIN);
     gpio_init(JUMP_BUTTON_PIN);   gpio_set_dir(JUMP_BUTTON_PIN,  GPIO_IN);  gpio_pull_up(JUMP_BUTTON_PIN);
     gpio_init(RESET_BUTTON_PIN);  gpio_set_dir(RESET_BUTTON_PIN, GPIO_IN);  gpio_pull_up(RESET_BUTTON_PIN);
 
     /* draw first frame */
     fillRect(0, 0, SCREEN_W, SCREEN_H, OB);
     drawMarioBaseRight(mario.local_x, mario.local_y);
     drawLevel(world_x);
     initStatusBar(0, 0);
 
     /* frame counter for throttling physics */
     uint8_t frame_counter = 0;
     // uint32_t game_over_ms   = 0;   // GAME OVER timing removed
 
     /* 2) main loop */
     while (true) {
        PT_SCHEDULE(timer_thread(&pt_timer));
 
         /* 2.2) read inputs (active-low) */
         bool left  =          !gpio_get(LEFT_BUTTON_PIN);
         bool right =          !gpio_get(RIGHT_BUTTON_PIN);
         bool jump  =          !gpio_get(JUMP_BUTTON_PIN);
         bool reset_pressed =  !gpio_get(RESET_BUTTON_PIN);
 
         /* 2.3) handle reset button press */
         if (reset_pressed) {
            coin.alive = false;
             // 1) Clear the screen
             fillRect(0, 0, SCREEN_W, SCREEN_H, OB);
 
             // 2) Reset *all* game state
             init_game();                // resets score, coins, timerr, prev_*, draws level & bar
             world_x      = 320.0f;      // back to center start
             game_over    = false;       // clear GAME OVER flag commented out
             game_over_drawn = false;    // clear GAME OVER drawn flag
             frame_counter = 0;          // restart your physics cadence
 
             // 3) Re-position Mario
             character_init(&mario, 50.0f, 418.0f);
 
             // 4) Restart your 1 Hz protothread
             PT_INIT(&pt_timer);
 
             // 5) Jump right back to the top of the loop
             continue;
         }
         
         if (game_over) {
            if (!game_over_drawn) {          
                drawGameOver(score, coins);
            }
         } else {
            
            if (++frame_counter >= PHYSICS_PERIOD) {

                if (timerr <= 0) {
                    game_over = true;
                    drawGameOver(score, coins);
                    continue;
                }

                frame_counter = 0;
    
                physics_update_character(&mario, left, right, jump);
                writeTimer(timerr);
    
                // if (mario.local_y >= (SCREEN_H - 30)) {
                //     game_over = true;  // GAME OVER fall detection commented
                // }
    
                /* (re)draw current frame after state change */
                drawLevel(world_x);
    
                // re-draw status bar
                if (coins != prev_coins || score != prev_score) {
                    //fillRect(352, 28, 55, 27, OB);
                    updateStatusBar(coins, score);
                    prev_coins = coins;
                    prev_score = score;
                }
         }
 
     }
 }
}
 
 /* ──────────────────────────────────────────────────────────
    Core 0: just launches core 1 (free for logging / CLI)
    ────────────────────────────────────────────────────────── */
 int main(void)
 {
     stdio_init_all();
     multicore_launch_core1(core1_main);
 
     /* idle loop on core 0 */
     while (true) { tight_loop_contents(); }
 
     return 0;   /* never reached */
 }
 