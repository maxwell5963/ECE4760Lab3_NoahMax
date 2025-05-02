/**
 * Hunter Adams (vha3@cornell.edu)
 *
 * Mario‑style side‑scroll demo running on core 1.
 * Core 0 is left free for USB / CLI tasks.
 *
 * HARDWARE CONNECTIONS
 *  - GPIO 16 → VGA Hsync
 *  - GPIO 17 → VGA Vsync
 *  - GPIO 18 → 470 Ω → VGA Green
 *  - GPIO 19 → 330 Ω → VGA Green
 *  - GPIO 20 → 330 Ω → VGA Blue
 *  - GPIO 21 → 330 Ω → VGA Red
 *  - RP2040 GND → VGA GND
 *
 * BUTTONS (pulled‑up, press to GND)
 *  - GPIO 10 → Move Left
 *  - GPIO 12 → Move Right
 *  - GPIO 11 → Jump
 *
 * RESOURCES USED
 *  - PIO state machines 0, 1, 2 on PIO instance 0
 *  - DMA channels (2, by claim mechanism)
 *  - 153.6 kB of RAM (pixel buffer)
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
 
 /* ─── constants ─────────────────────────────────────────── */
 #define SCREEN_W            640
 #define SCREEN_H            480
 
 /* Button pins (pulled‑up; short to GND when pressed) */
 #define LEFT_BUTTON_PIN     10
 #define RIGHT_BUTTON_PIN    12
 #define JUMP_BUTTON_PIN     11   /* NEW */
 
 /* ─── global game state ─────────────────────────────────── */
 Character mario;
 float     world_x = 320.0f;
 
 /* ──────────────────────────────────────────────────────────
    Core 1: complete game loop
    ────────────────────────────────────────────────────────── */
 void core1_main(void)
 {
     /* 1) one‑time init */
     initVGA();
     initLevel();
     character_init(&mario, 50.0f, 418.0f);
 
     /* buttons: inputs + pull‑ups */
     gpio_init(LEFT_BUTTON_PIN);   gpio_set_dir(LEFT_BUTTON_PIN,  GPIO_IN); gpio_pull_up(LEFT_BUTTON_PIN);
     gpio_init(RIGHT_BUTTON_PIN);  gpio_set_dir(RIGHT_BUTTON_PIN, GPIO_IN); gpio_pull_up(RIGHT_BUTTON_PIN);
     gpio_init(JUMP_BUTTON_PIN);   gpio_set_dir(JUMP_BUTTON_PIN,  GPIO_IN); gpio_pull_up(JUMP_BUTTON_PIN);
 
     /* draw first frame */
     fillRect(0, 0, SCREEN_W, SCREEN_H, OB);
     drawMarioBase(mario.local_x, mario.local_y);
 
     /* 2) main loop */
     while (true) {
         clearscreen(world_x);                 /* wipe prior frame */
 
         /* read inputs (active‑low) */
         bool left  = !gpio_get(LEFT_BUTTON_PIN);
         bool right = !gpio_get(RIGHT_BUTTON_PIN);
         bool jump  = !gpio_get(JUMP_BUTTON_PIN);   /* NEW */
 
         /* physics + scrolling */
         physics_update_character(&mario, left, right, jump);
 
         /* render level */
         drawLevel(world_x);
     }
 }
 
 /* ──────────────────────────────────────────────────────────
    Core 0: just launches core 1 (free for logging / CLI)
    ────────────────────────────────────────────────────────── */
 int main(void)
 {
     stdio_init_all();
     multicore_launch_core1(core1_main);
 
     /* idle loop on core 0 */
     while (true) { tight_loop_contents(); }
 
     return 0;   /* never reached */
 }
 