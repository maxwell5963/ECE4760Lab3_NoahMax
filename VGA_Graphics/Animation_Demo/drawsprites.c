/******************************************************************************
 * File: drawsprites.c
 * 
 * Authors: Max Warner (mtw82), Noah Wilson (njw66)
 *
 * Description:
 *    This source file defines sprite arrays and draw functions for our
 *    Super Mario Bros-inspired ECE 4760 final project.
 ******************************************************************************/
 
 #include "drawsprites.h"
 #include "colors.h"
 #include <stdint.h>  
 #include "vga16_graphics.h"
  
 const uint16_t goombaframe1[GOOMBA_SIZE][GOOMBA_SIZE] = {
     {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, RD, RD, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, RD, RD, OB, OB, OB, OB},
     {OB, OB, OB, OB, RD, RD, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, RD, RD, OB, OB, OB, OB},
     {OB, OB, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, OB, OB},
     {OB, OB, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, OB, OB},
     {OB, OB, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, OB, OB},
     {OB, OB, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, OB, OB},
     {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
     {OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB},
     {OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB},
     {OB, OB, OB, OB, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB},
     {OB, OB, OB, OB, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB},
     {OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB},
     {OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB},
     {OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB}
 };
 
  // Second Goomba Animation Frame
 const uint16_t goombaframe2[GOOMBA_SIZE][GOOMBA_SIZE] = {
     {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, RD, RD, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, RD, RD, OB, OB, OB, OB},
     {OB, OB, OB, OB, RD, RD, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, RD, RD, OB, OB, OB, OB},
     {OB, OB, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, OB, OB},
     {OB, OB, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, OB, OB},
     {OB, OB, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, OB, OB},
     {OB, OB, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, OB, OB},
     {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
     {OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB},
     {OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, OB, OB, OB, OB},
     {OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, OB, OB, OB, OB},
     {OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB},
     {OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB},
     {OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB},
 };
 
  // Goomba Dead Sprite
 const uint16_t goomba_dead[GOOMBA_DEAD_H][GOOMBA_DEAD_W] = {
     {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB},
     {OB, OB, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, OB, OB},
     {OB, OB, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, OB, OB},
     {RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, WT, WT, BL, BL, BL, BL, BL, BL, WT, WT, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD},
     {RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, WT, WT, BL, BL, BL, BL, BL, BL, WT, WT, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
     {OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB},
     {OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB},
 };
 
 // Goomba Dead Sprite
 const uint16_t goomba_dead_flipped[GOOMBA_DEAD_H][GOOMBA_DEAD_W] = {
     {OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB},
     {OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB},
     {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, WT, WT, BL, BL, BL, BL, BL, BL, WT, WT, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD},
     {RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, WT, WT, BL, BL, BL, BL, BL, BL, WT, WT, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD},
     {OB, OB, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, OB, OB},
     {OB, OB, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, OB, OB},
     {OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
 };
 
 // Coin Sprite 
 const uint16_t coin_sprite[COIN_H][COIN_W] = {
     {OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB},
     {OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB},
     {OB, OB, BL, BL, WT, WT, WT, WT, WT, WT, WT, BL, BL, OB, OB},
     {OB, OB, BL, BL, YL, YL, YL, YL, YL, YL, YL, BL, BL, OB, OB},
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
     {BL, BL, WT, YL, YL, YL, BL, BL, BL, YL, YL, YL, DO, BL, BL},
     {BL, BL, WT, YL, YL, YL, YL, YL, YL, YL, YL, YL, DO, BL, BL},
     {OB, OB, BL, BL, YL, YL, YL, YL, YL, YL, YL, BL, BL, OB, OB},
     {OB, OB, BL, BL, YL, YL, YL, DO, DO, DO, DO, BL, BL, OB, OB},
     {OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB},
     {OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB},
 };
 
 // Mario base sprite (standing around) 
 const uint16_t mario_base_right[MARIO_H][MARIO_W] = {
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, LO, LO, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, LO, LO, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, BL, BL, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, BL, BL, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, BL, BL, LO, LO, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, LO, OB},
    {OB, OB, OB, OB, OB, OB, BL, BL, LO, LO, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, LO, OB},
    {OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, DB, DB, DB, DB, DB, DB, DB, DB, RD, RD, DB, DB, DB, DB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, DB, DB, DB, DB, DB, DB, DB, DB, RD, RD, DB, DB, RD, RD, DB, DB, DB, DB, DB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, RD, RD, RD, RD, RD, RD, DB, DB, DB, DB, DB, DB, DB, OB, OB, OB},
    {OB, OB, OB, OB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, RD, RD, RD, RD, RD, RD, DB, DB, DB, DB, DB, DB, DB, OB, OB, OB},
    {OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, DB, DB, RD, RD, LO, LO, RD, RD, LO, LO, RD, RD, DB, DB, LO, LO, LO, LO, OB, OB},
    {OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, DB, DB, RD, RD, LO, LO, RD, RD, LO, LO, RD, RD, DB, DB, LO, LO, LO, LO, OB, OB},
    {OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LO, LO, LO, LO, LO, LO, OB, OB},
    {OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LO, LO, LO, LO, LO, LO, OB, OB},
    {OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LO, LO, LO, LO, OB, OB},
    {OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LO, LO, LO, LO, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB},
    {OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB},
    {OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL},
    {OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL},
};

// Mario running 
 const uint16_t mario_run_right[MARIO_H][MARIO_W] = {
     {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, LO, LO, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, LO, LO, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, BL, BL, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, BL, BL, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, BL, BL, LO, LO, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, LO, OB},
     {OB, OB, OB, OB, OB, OB, BL, BL, LO, LO, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, LO, OB},
     {OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, DB, DB, RD, RD, RD, RD, DB, DB, DB, DB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, DB, DB, RD, RD, RD, RD, DB, DB, DB, DB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, OB, DB, DB, DB, DB, DB, DB, DB, DB, RD, RD, RD, RD, RD, RD, DB, DB, DB, DB, DB, DB, LO, LO, LO, LO, LO, OB},
     {OB, OB, OB, OB, DB, DB, DB, DB, DB, DB, DB, DB, RD, RD, RD, RD, RD, RD, DB, DB, DB, DB, DB, DB, LO, LO, LO, LO, LO, OB},
     {OB, LO, LO, LO, DB, DB, DB, DB, DB, DB, DB, DB, RD, RD, LO, LO, RD, RD, RD, RD, RD, RD, DB, DB, DB, DB, LO, LO, LO, OB},
     {OB, LO, LO, LO, DB, DB, DB, DB, DB, DB, DB, DB, RD, RD, LO, LO, RD, RD, RD, RD, RD, RD, DB, DB, DB, DB, LO, LO, LO, OB},
     {OB, LO, LO, LO, LO, LO, OB, OB, DB, DB, DB, DB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, BL, BL, OB, OB},
     {OB, LO, LO, LO, LO, LO, OB, OB, DB, DB, DB, DB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, BL, BL, OB, OB},
     {OB, LO, LO, LO, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, BL, BL, BL, BL, OB, OB},
     {OB, LO, LO, LO, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, OB, OB},
     {OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, OB, OB},
     {OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, OB, OB},
     {OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, OB, OB},
     {OB, OB, OB, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
     {OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
 };
 
 // Mario running (midstride)
 const uint16_t mario_run_midstride_right[MARIO_H][MARIO_W] = {
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, LO, LO, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, LO, LO, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, BL, BL, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, BL, BL, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, BL, BL, LO, LO, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, LO, OB},
    {OB, OB, OB, OB, OB, OB, BL, BL, LO, LO, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, LO, OB},
    {OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, OB, OB, LO, LO, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, OB, OB, LO, LO, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, LO, LO, DB, DB, YL, YL, DB, DB, DB, YL, YL, DB, DB, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, LO, LO, DB, DB, YL, YL, DB, DB, DB, YL, YL, DB, DB, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, LO, LO, LO, LO, RD, RD, RD, RD, DB, DB, DB, RD, RD, RD, RD, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, LO, LO, LO, LO, RD, RD, RD, RD, DB, DB, DB, RD, RD, RD, RD, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, BL, BL, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, BL, BL, RD, RD, RD, RD, RD, RD, OB, OB, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, OB, OB, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, OB, OB, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
};


const uint16_t mario_base_left[MARIO_H][MARIO_W] = {
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, LO, LO, BL, BL, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, LO, LO, BL, BL, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, BL, BL, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, BL, BL, OB, OB, OB, OB, OB, OB},
    {OB, LO, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, LO, LO, BL, BL, OB, OB, OB, OB, OB, OB},
    {OB, LO, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, LO, LO, BL, BL, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, DB, DB, DB, DB, RD, RD, DB, DB, DB, DB, DB, DB, DB, DB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, DB, DB, DB, DB, DB, RD, RD, DB, DB, RD, RD, DB, DB, DB, DB, DB, DB, DB, DB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, DB, DB, DB, DB, DB, DB, DB, RD, RD, RD, RD, RD, RD, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, OB, OB, OB, OB},
    {OB, OB, OB, DB, DB, DB, DB, DB, DB, DB, RD, RD, RD, RD, RD, RD, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, OB, OB, OB, OB},
    {OB, OB, LO, LO, LO, LO, DB, DB, RD, RD, LO, LO, RD, RD, LO, LO, RD, RD, DB, DB, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB},
    {OB, OB, LO, LO, LO, LO, DB, DB, RD, RD, LO, LO, RD, RD, LO, LO, RD, RD, DB, DB, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB},
    {OB, OB, LO, LO, LO, LO, LO, LO, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB},
    {OB, OB, LO, LO, LO, LO, LO, LO, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB},
    {OB, OB, LO, LO, LO, LO, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB},
    {OB, OB, LO, LO, LO, LO, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB},
    {OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB},
    {OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB},
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB},
    {BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB},
};

const uint16_t mario_run_left[MARIO_H][MARIO_W] = {
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, LO, LO, BL, BL, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, LO, LO, BL, BL, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, BL, BL, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, BL, BL, OB, OB, OB, OB, OB, OB},
    {OB, LO, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, LO, LO, BL, BL, OB, OB, OB, OB, OB, OB},
    {OB, LO, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, LO, LO, BL, BL, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, DB, DB, DB, DB, RD, RD, RD, RD, DB, DB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, DB, DB, DB, DB, RD, RD, RD, RD, DB, DB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, LO, LO, LO, LO, LO, DB, DB, DB, DB, DB, DB, RD, RD, RD, RD, RD, RD, DB, DB, DB, DB, DB, DB, DB, DB, OB, OB, OB, OB},
    {OB, LO, LO, LO, LO, LO, DB, DB, DB, DB, DB, DB, RD, RD, RD, RD, RD, RD, DB, DB, DB, DB, DB, DB, DB, DB, OB, OB, OB, OB},
    {OB, LO, LO, LO, DB, DB, DB, DB, RD, RD, RD, RD, RD, RD, LO, LO, RD, RD, DB, DB, DB, DB, DB, DB, DB, DB, LO, LO, LO, OB},
    {OB, LO, LO, LO, DB, DB, DB, DB, RD, RD, RD, RD, RD, RD, LO, LO, RD, RD, DB, DB, DB, DB, DB, DB, DB, DB, LO, LO, LO, OB},
    {OB, OB, BL, BL, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, DB, DB, DB, DB, OB, OB, LO, LO, LO, LO, LO, OB},
    {OB, OB, BL, BL, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, DB, DB, DB, DB, OB, OB, LO, LO, LO, LO, LO, OB},
    {OB, OB, BL, BL, BL, BL, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, LO, LO, LO, OB},
    {OB, OB, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, LO, LO, LO, OB},
    {OB, OB, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB},
    {OB, OB, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB},
};

const uint16_t mario_run_midstride_left[MARIO_H][MARIO_W] = {
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, LO, LO, BL, BL, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, LO, LO, BL, BL, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, BL, BL, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, BL, BL, OB, OB, OB, OB, OB, OB},
    {OB, LO, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, LO, LO, BL, BL, OB, OB, OB, OB, OB, OB},
    {OB, LO, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, LO, LO, BL, BL, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, LO, LO, OB, OB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, LO, LO, OB, OB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, DB, DB, YL, YL, DB, DB, DB, YL, YL, DB, DB, LO, LO, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, LO, LO, LO, LO, LO, LO, DB, DB, YL, YL, DB, DB, DB, YL, YL, DB, DB, LO, LO, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, RD, RD, RD, RD, DB, DB, DB, RD, RD, RD, RD, LO, LO, LO, LO, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, LO, LO, LO, LO, RD, RD, RD, RD, DB, DB, DB, RD, RD, RD, RD, LO, LO, LO, LO, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, OB, OB, RD, RD, RD, RD, RD, RD, BL, BL, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, OB, OB, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, RD, RD, RD, RD, RD, OB, OB, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
    {OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, BL, BL, BL, BL, BL, BL, BL, BL, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB, OB},
};

 //─── draw-functions ────────────────────────────────────────────────────
 
 void DrawSprite(short x0, short y0, const uint16_t *sprite, short w, short h) {
     for (short row = 0; row < h; row++) {
         for (short col = 0; col < w; col++) {
             // load the color from the flat array
             uint16_t c = sprite[row * w + col];
             if (c == CY) continue; 
             drawPixel(x0 + col, y0 + row, (char)c);
         }
     }
 }
 
 // wrappers for drawing each individual sprite
 void drawGoombaFrame1(short x, short y) {
     DrawSprite(x, y, &goombaframe1[0][0], GOOMBA_SIZE, GOOMBA_SIZE);
 }
 
 void drawGoombaFrame2(short x, short y) {
     DrawSprite(x, y, &goombaframe2[0][0], GOOMBA_SIZE, GOOMBA_SIZE);
 }
 
 void drawGoombaDead(short x, short y) {
     DrawSprite(x, y, &goomba_dead[0][0], GOOMBA_DEAD_W, GOOMBA_DEAD_H);
 }
 
 void drawGoombaDeadFlipped(short x, short y) {
     DrawSprite(x, y, &goomba_dead_flipped[0][0], GOOMBA_DEAD_W, GOOMBA_DEAD_H);
 }
 
 void drawCoinSprite(short x, short y) {
     DrawSprite(x, y, &coin_sprite[0][0], COIN_W, COIN_H);
 }
 
 void drawMarioBaseRight(short x, short y) {
     DrawSprite(x, y, &mario_base_right[0][0], MARIO_W, MARIO_H);
 }
 

 void drawMarioRunRight(short x, short y) {
     DrawSprite(x, y, &mario_run_right[0][0], MARIO_W, MARIO_H);
 }

 void drawMarioMidStrideRight(short x, short y) {
    DrawSprite(x, y, &mario_run_midstride_right[0][0], MARIO_W, MARIO_H);
}

void drawMarioBaseLeft(short x, short y) {
    DrawSprite(x, y, &mario_base_left[0][0], MARIO_W, MARIO_H);
}

void drawMarioRunLeft(short x, short y) {
    DrawSprite(x, y, &mario_run_left[0][0], MARIO_W, MARIO_H);
}

void drawMarioMidStrideLeft(short x, short y) {
   DrawSprite(x, y, &mario_run_midstride_left[0][0], MARIO_W, MARIO_H);
}