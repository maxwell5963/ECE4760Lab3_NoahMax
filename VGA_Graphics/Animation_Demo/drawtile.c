/******************************************************************************
 * File: tiles.c
 * 
 * Authors: Max Warner (mtw82), Noah Wilson (njw66)
 *
 * Description:
 *    This source file defines tile arrays and draw functions for our
 *    Super Mario Bros-inspired ECE 4760 final project.
  ******************************************************************************/
  
  #include "drawtile.h"
  #include "colors.h"
  #include <stdint.h>  
  #include "vga16_graphics.h"
    
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

  const uint16_t flag_pole[30][30] = {
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
{OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, WT, WT, WT, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 

  };

  const uint16_t flag[30][30] = {
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, }, 
    
      };
 
      void drawFlagPole(short x, short y) {
           DrawTile(x, y, &flag_pole[0][0]);
      }

      void drawFlag(short x, short y) {
        DrawTile(x, y, &flag[0][0]);
   }
  //──────────────────────────────────────────────────────────────────────────────
  // Core draw routine: renders a TILE_SIZE×TILE_SIZE block of pixels
  //
  //   x0, y0 : top-left corner on screen
  //   tile    : flattened pointer to TILE_SIZE×TILE_SIZE color array
  //──────────────────────────────────────────────────────────────────────────────
  void DrawTile(short x0, short y0, const uint16_t *tile) {
      for (short row = 0; row < TILE_SIZE; row++) {
          for (short col = 0; col < TILE_SIZE; col++) {
              // fetch color from the flattened 2D array
              uint16_t color = tile[row * TILE_SIZE + col];
              if (color != TR) {
                drawPixel(x0 + col, y0 + row, (char)color);
              }
          }
      }
  }
  
  //──────────────────────────────────────────────────────────────────────────────
  // Convenience wrappers for each tile type
  //──────────────────────────────────────────────────────────────────────────────
  
  /** Draws the ground tile at (x, y). */
  void drawGroundTile(short x, short y) {
      DrawTile(x, y, &ground_tile[0][0]);
  }
  
  /** Draws the stair tile at (x, y). */
  void drawStairTile(short x, short y) {
      DrawTile(x, y, &stair_tile[0][0]);
  }
  
  /** Draws the floating brick tile at (x, y). */
  void drawFloatyBrick(short x, short y) {
      DrawTile(x, y, &floaty_brick[0][0]);
  }
  
  /** Draws the mystery box (frame 1) at (x, y). */
  void drawMysteryBox(short x, short y) {
      DrawTile(x, y, &mystery_box[0][0]);
  }
  
  /** Draws the mystery box (frame 2) at (x, y). */
  void drawMysteryBox2(short x, short y) {
      DrawTile(x, y, &mystery_box_frame2[0][0]);
  }
  
  
  //──────────────────────────────────────────────────────────────────────────────
  // Pipe tile stubs (arrays to be defined later)
  //──────────────────────────────────────────────────────────────────────────────
  
  /** Draws the top-left pipe segment at (x, y). */
  void drawPipeTopLeft(short x, short y) {
      //DrawTile(x, y, &pipe_top_left[0][0]);
      fillRect(x, y, 30, 30, DARK_GREEN);
  }
  
  /** Draws the top-right pipe segment at (x, y). */
  void drawPipeTopRight(short x, short y) {
      //DrawTile(x, y, &pipe_top_right[0][0]);
      fillRect(x, y, 30, 30, DARK_GREEN);
  }
  
  /** Draws the bottom-left pipe segment at (x, y). */
  void drawPipeBotLeft(short x, short y) {
      //DrawTile(x, y, &pipe_bot_left[0][0]);
      fillRect(x, y, 30, 30, DARK_GREEN);
  }
  
  /** Draws the bottom-right pipe segment at (x, y). */
  void drawPipeBotRight(short x, short y) {
      //DrawTile(x, y, &pipe_bot_right[0][0]);
      fillRect(x, y, 30, 30, DARK_GREEN);
  }
  

  
  
  
  