/******************************************************************************
 * File: sprite_library.h
 * 
 * Authors: Max Warner (mtw82), Noah Wilson (njw66)
 *
 * Description:
 *    This header file defines the sprite data and associated constants for our
 *    Super Mario Bros-inspired ECE 4760 final project.
 *
 *    We keep our sprite definitions in a dedicated header which
 *    helps prevent accidental modification — especially when working with AI 
 *    assistance tools or collaborative editing environments.
 *
 *    Arrays defined here are declared as `extern` to ensure single instantiation
 *    in the associated source (.c) file, allowing for efficient memory usage.
 ******************************************************************************/

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
 #include "pt_cornell_rp2040_v1_3.h"
 #include "vga16_graphics.h"
 
 #define LEVEL_DATA_H
 #define TILE_SIZE 30
 #define EMPTY -1

 #define DO 0x924B14 //dark orange (brown)
 #define BL 0x0000 //black
 #define LO 0xF0AC3F //light orange 
 #define LB 0x6481F9 //light blue for sky 
 #define RD 0xB92716 //red
 #define TN 0x736702 // dark tan for mario's outfit
 #define LG 0x74F01C // lime green
 #define DG 0x138400 // dark green
 #define WT 0xFFFFFF // white
 #define YL 0xFFFF00 //yellow
 #define BS // blank space 

 // First Goomba Animation Frame
const uint16_t goombaframe1[30][30] = {
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, RD, RD, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, RD, RD, LB, LB, LB, LB},
    {LB, LB, LB, LB, RD, RD, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, RD, RD, LB, LB, LB, LB},
    {LB, LB, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, LB, LB},
    {LB, LB, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, LB, LB},
    {LB, LB, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, LB, LB},
    {LB, LB, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, LB, LB},
    {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
    {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
    {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
    {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
    {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
    {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
    {LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB},
    {LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, RD, RD, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, RD, RD, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, RD, RD, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, RD, RD, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, LB, LB, LB, LB},
    {LB, LB, LB, LB, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB},
    {LB, LB, LB, LB, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB},
    {LB, LB, LB, LB, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB},
    {LB, LB, LB, LB, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB},
    {LB, LB, LB, LB, LB, LB, BL, BL, BL, BL, BL, BL, LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, BL, BL, BL, BL, BL, BL, LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB, LB, LB}
};

 // Second Goomba Animation Frame
 const uint16_t goombaframe2[30][30] = {
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, RD, RD, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, RD, RD, LB, LB, LB, LB},
    {LB, LB, LB, LB, RD, RD, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, RD, RD, LB, LB, LB, LB},
    {LB, LB, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, LB, LB},
    {LB, LB, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, LB, LB},
    {LB, LB, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, LB, LB},
    {LB, LB, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, LB, LB},
    {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
    {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
    {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
    {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
    {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
    {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
    {LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB},
    {LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, RD, RD, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, RD, RD, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, RD, RD, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, RD, RD, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, LB, LB, LB, LB},
    {LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, LB, LB, LB, LB},
    {LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, LB, LB, LB, LB},
    {LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, LB, LB, LB, LB},
    {LB, LB, LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB, BL, BL, BL, BL, BL, BL, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB, BL, BL, BL, BL, BL, BL, LB, LB, LB, LB, LB, LB},
};

 // Goomba Dead Sprite
const uint16_t goomba_dead[16][30] = {
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB},
    {LB, LB, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, LB, LB},
    {LB, LB, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, LB, LB},
    {RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, WT, WT, BL, BL, BL, BL, BL, BL, WT, WT, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD},
    {RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, WT, WT, BL, BL, BL, BL, BL, BL, WT, WT, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD},
    {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
    {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
    {LB, LB, LB, LB, LB, LB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB, LB, LB, LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB},
    {LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB, LB, LB, LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB},
};

// Goomba Dead Sprite
const uint16_t goomba_dead_flipped[16][30] = {
    {LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB, LB, LB, LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB},
    {LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB, LB, LB, LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LB, LB, LB, LB, LB, LB},
    {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
    {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
    {RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, WT, WT, BL, BL, BL, BL, BL, BL, WT, WT, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD},
    {RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, WT, WT, BL, BL, BL, BL, BL, BL, WT, WT, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD},
    {LB, LB, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, LB, LB},
    {LB, LB, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, LB, LB},
    {LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
};

 // Powerup Mushroom Spirte
 const uint16_t powerup_mushroom[30][30] = {
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, BL, BL, BL, BL, WT, WT, DO, DO, DO, DO, DO, DO, WT, WT, BL, BL, BL, BL, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, BL, BL, BL, BL, WT, WT, DO, DO, DO, DO, DO, DO, WT, WT, BL, BL, BL, BL, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, BL, BL, WT, WT, WT, WT, DO, DO, DO, DO, DO, DO, DO, DO, WT, WT, WT, WT, WT, WT, BL, BL, LB, LB, LB, LB},
    {LB, LB, LB, LB, BL, BL, WT, WT, WT, WT, DO, DO, DO, DO, DO, DO, DO, DO, WT, WT, WT, WT, WT, WT, BL, BL, LB, LB, LB, LB},
    {LB, LB, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, LB, LB},
    {LB, LB, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, LB, LB},
    {BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, WT, WT, WT, WT, WT, WT, WT, WT, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {BL, BL, DO, DO, DO, DO, DO, DO, DO, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {BL, BL, DO, DO, DO, DO, DO, DO, DO, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, DO, DO, DO, WT, WT, WT, WT, DO, DO, BL, BL},
    {BL, BL, DO, DO, DO, DO, DO, DO, DO, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, DO, DO, DO, WT, WT, WT, WT, DO, DO, BL, BL},
    {BL, BL, WT, WT, WT, WT, DO, DO, DO, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, DO, WT, WT, WT, WT, WT, WT, WT, WT, BL, BL},
    {BL, BL, WT, WT, WT, WT, DO, DO, DO, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, DO, WT, WT, WT, WT, WT, WT, WT, WT, BL, BL},
    {BL, BL, WT, WT, WT, WT, WT, WT, DO, DO, WT, WT, WT, WT, WT, WT, WT, WT, DO, DO, WT, WT, WT, WT, WT, WT, WT, WT, BL, BL},
    {BL, BL, WT, WT, WT, WT, WT, WT, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, WT, WT, WT, WT, WT, WT, WT, WT, BL, BL},
    {BL, BL, BL, BL, WT, WT, WT, WT, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, WT, WT, WT, WT, WT, WT, BL, BL, BL, BL},
    {BL, BL, BL, BL, WT, WT, WT, WT, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, WT, WT, WT, WT, WT, WT, BL, BL, BL, BL},
    {LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB},
    {LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB},
    {LB, LB, LB, LB, LB, LB, BL, BL, WT, WT, WT, WT, BL, BL, WT, WT, BL, BL, WT, WT, WT, WT, BL, BL, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, BL, BL, WT, WT, WT, WT, BL, BL, WT, WT, BL, BL, WT, WT, WT, WT, BL, BL, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, BL, BL, WT, WT, WT, WT, WT, WT, BL, BL, WT, WT, BL, BL, WT, WT, WT, WT, WT, WT, BL, BL, LB, LB, LB, LB},
    {LB, LB, LB, LB, BL, BL, WT, WT, WT, WT, WT, WT, BL, BL, WT, WT, BL, BL, WT, WT, WT, WT, WT, WT, BL, BL, LB, LB, LB, LB},
    {LB, LB, LB, LB, BL, BL, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, BL, BL, LB, LB, LB, LB},
    {LB, LB, LB, LB, BL, BL, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, BL, BL, LB, LB, LB, LB},
    {LB, LB, LB, LB, BL, BL, BL, BL, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, BL, BL, BL, BL, LB, LB, LB, LB},
    {LB, LB, LB, LB, BL, BL, BL, BL, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, WT, BL, BL, BL, BL, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LB, LB, LB, LB, LB, LB},
};

// Coin Sprite 
const uint16_t coin_sprite[15][25] ={
    {LB, LB, LB, LB, BL, BL, BL, BL, BL, BL, BL, LB, LB, LB, LB},
    {LB, LB, LB, LB, BL, BL, BL, BL, BL, BL, BL, LB, LB, LB, LB},
    {LB, LB, BL, BL, WT, WT, WT, WT, WT, WT, WT, BL, BL, LB, LB},
    {LB, LB, BL, BL, YL, YL, YL, YL, YL, YL, YL, BL, BL, LB, LB},
    {BL, BL, WT, YL, YL, YL, YL, YL, YL, YL, YL, YL, DO, BL, BL},
    {BL, BL, WT, YL, YL, YL, YL, YL, YL, YL, YL, YL, DO, BL, BL},
    {BL, BL, WT, YL, YL, YL, WT, WT, WT, WT, YL, YL, DO, BL, BL},
    {BL, BL, WT, YL, YL, WT, YL, YL, YL, BL, YL, YL, DO, BL, BL},
    {BL, BL, WT, YL, YL, WT, YL, YL, YL, BL, YL, YL, DO, BL, BL},
    {BL, BL, WT, YL, YL, WT, YL, YL, YL, BL, YL, YL, DO, BL, BL},
    {BL, BL, WT, YL, YL, WT, YL, YL, YL, BL, YL, YL, DO, BL, BL},
    {BL, BL, WT, YL, YL, WT, YL, YL, YL, BL, YL, YL, DO, BL, BL},
    {BL, BL, WT, YL, YL, WT, YL, YL, YL, BL, YL, YL, DO, BL, BL},
    {BL, BL, WT, YL, YL, WT, YL, YL, YL, BL, YL, YL, DO, BL, BL},
    {BL, BL, WT, YL, YL, WT, YL, YL, YL, BL, YL, YL, DO, BL, BL},
    {BL, BL, WT, YL, YL, WT, YL, YL, YL, BL, YL, YL, DO, BL, BL},
    {BL, BL, WT, YL, YL, WT, YL, YL, YL, BL, YL, YL, DO, BL, BL},
    {BL, BL, WT, YL, YL, WT, YL, YL, YL, BL, YL, YL, DO, BL, BL},
    {BL, BL, WT, YL, YL, WT, YL, YL, YL, BL, YL, YL, DO, BL, BL},
    {BL, BL, WT, YL, YL, WT, YL, YL, YL, BL, YL, YL, DO, BL, BL},
    {BL, BL, WT, YL, YL, YL, BL, BL, BL, YL, YL, YL, DO, BL, BL},
    {BL, BL, WT, YL, YL, YL, YL, YL, YL, YL, YL, YL, DO, BL, BL},
    {LB, LB, BL, BL, YL, YL, YL, YL, YL, YL, YL, BL, BL, LB, LB},
    {LB, LB, BL, BL, YL, YL, YL, DO, DO, DO, DO, BL, BL, LB, LB},
    {LB, LB, LB, LB, BL, BL, BL, BL, BL, BL, BL, LB, LB, LB, LB},
    {LB, LB, LB, LB, BL, BL, BL, BL, BL, BL, BL, LB, LB, LB, LB},
};

// Mario base sprite (standing around) (WIP)
const uint16_t mario_base[30][32] {
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
    {LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB, LB},
};

// Turtle walk 1

// Turtle walk 2

//