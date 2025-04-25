/******************************************************************************
 * File: tile_library.h
 * 
 * Authors: Max Warner (mtw82), Noah Wilson (njw66)
 *
 * Description:
 *    This header file defines the tilemap data and associated constants for our
 *    Super Mario Bros-inspired ECE 4760 final project.
 *
 *    Additionally, keeping level and tile definitions in a dedicated header 
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
#define DO 0x924B14 //dark orange (brown)
#define BL 0x00000 //black
#define LO 0xF0AC3F //light orange 
#define LB 0x6481F9 //light blue for sky 
#define RD 0xB92716 //red
#define TN 0x736702 // dark tan for mario's outfit
#define LG 0x74F01C // lime green
#define DG 0x138400 // dark green
#define WT 0xFFFFFF // white
#define YL 0xFFFF00 //yellow 
#define BS // blank space 


#if 0
// We can only produce 16 (4-bit) colors, so let's give them readable names - usable in main()
enum colors {BL, DARK_GREEN, MED_GREEN, GREEN,
    DARK_BLUE, BLUE, LB, CYAN,
    RED, DO, LO, YELLOW, 
    MAGENTA, PINK, LIGHT_PINK, WHITE} ;
#endif

// Definition of a ground tile array
const uint16_t ground_tile[30][30] = {
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL},
    {LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {LO, LO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {LO, LO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {LO, LO, BL, BL, BL, BL, BL, BL, BL, DO, DO, DO, DO, BL, BL, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, DO, DO, BL, BL, BL, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, DO, DO, BL, BL, BL, BL, BL, BL, BL, BL, BL, DO, DO, DO, DO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL},
    {LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL},
    {LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, LO, LO, DO, DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL},
    {LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, LO, LO, DO, DO, DO, DO, DO, DO, LO, LO, LO, LO, LO, BL, BL},
    {LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, BL, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, LO, LO, BL, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, LO, LO, LO, LO, BL, BL, BL, BL, BL, DO, DO, DO, DO, DO, BL, BL, BL},
    {BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, DO, DO, DO, BL, BL, BL, BL},
    {BL, BL, DO, DO, DO, DO, DO, DO, DO, BL, BL, LO, LO, LO, DO, DO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL},
    {BL, BL, DO, DO, DO, DO, DO, DO, BL, BL, LO, LO, LO, DO, DO, DO, DO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, DO, DO, DO},
    {BL, BL, BL, DO, DO, DO, DO, DO, BL, BL, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, LO, LO, LO, LO, LO, DO, DO, DO, DO, DO},
    {DO, BL, BL, BL, BL, DO, DO, BL, BL, BL, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, LO, LO, LO, LO, LO, LO, LO, LO},
    {DO, DO, BL, BL, BL, BL, BL, BL, BL, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, LO, LO, LO, LO, LO},
    {DO, DO, DO, DO, BL, BL, BL, BL, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, LO, LO, DO},
    {DO, DO, DO, DO, DO, BL, BL, BL, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, LO, LO, LO, DO},
    {DO, DO, DO, DO, BL, BL, BL, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, LO, LO, DO, DO, DO},
    {DO, DO, DO, DO, BL, BL, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, BL, LO, LO, DO, DO, DO},
};

//Definition of a stair tile array
const uint16_t stair_tile[30][30] = {
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL},
    {LO, LO, DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL},
    {LO, LO, DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL},
    {LO, LO, LO, LO, DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL},
    {LO, LO, LO, LO, DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL},
    {LO, LO, LO, LO, LO, LO, DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, BL},
    {LO, LO, LO, LO, LO, LO, DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, BL},
    {LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, BL, BL, BL, BL, BL},
    {LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, BL, BL, BL, BL, BL},
    {LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, BL, BL, BL, BL, BL},
    {LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, BL, BL, BL, BL, BL},
    {LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, BL, BL, BL, BL, BL},
    {LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, BL, BL, BL, BL, BL},
    {LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, BL, BL, BL, BL, BL},
    {LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, BL, BL, BL, BL, BL},
    {LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, BL, BL, BL, BL, BL},
    {LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, BL, BL, BL, BL, BL},
    {LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, BL, BL, BL, BL, BL},
    {LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, BL, BL, BL, BL, BL},
    {LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, BL, BL, BL, BL, BL},
    {LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, BL, BL, BL, BL, BL, BL},
    {LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, DO, DO, BL, BL, BL, BL, BL, BL},
    {LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, DO, DO, BL, BL, BL, BL, BL, BL},
    {LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, DO, DO, BL, BL, BL, BL},
    {LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, DO, DO, BL, BL, BL, BL},
    {LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, DO, DO, BL, BL},
    {LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, DO, DO, BL, BL},
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, DO, DO},
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, DO, DO},
};


//definition of a floaty brick tile array
const uint16_t floaty_brick[30][30] = {
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL},
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL,},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL,},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL,},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL,},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL,},
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL},
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL},
    {DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO},
    {DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO},
    {DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO},
    {DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO},
    {DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO},
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL},
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL,},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL,},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL,},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL,},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL,},
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL},
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL},
    {DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO},
    {DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO},
    {DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO},
    {DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO},
    {DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO},
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL},
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL},
};


// Definition of a mystery box array
const uint16_t mystery_box[30][30] = {
    {LB, LB, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, LB, LB},
    {LB, LB, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, LB, LB},
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, BL, BL},
    {DO, DO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, LO, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, DO, DO, DO, DO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, BL, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, DO, DO, DO, DO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, BL, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, DO, DO, DO, DO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, BL, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, DO, DO, DO, DO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, BL, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, DO, DO, DO, DO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, BL, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, DO, DO, BL, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, DO, DO, BL, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, BL, BL, BL, BL, BL, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, DO, DO, DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, BL, BL},
    {DO, DO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL},
    {DO, DO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL},
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL},
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL},
};

// Definition of the Mystery Box Frame 2 (blank)
const uint16_t mystery_box_frame2[30][30] = {
    {LB, LB, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, LB, LB},
    {LB, LB, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, LB, LB},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, BL, BL},
    {DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, BL, BL},
    {DO, DO, DO, DO, BL, BL, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, DO, BL, BL},
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL},
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL},
};

// Top Right Corner of the Pipe

// Top Left Corner of the Pipe

// Bottom Right Corner of the Pipe

// Bottom Left Corner of the Pipe

//