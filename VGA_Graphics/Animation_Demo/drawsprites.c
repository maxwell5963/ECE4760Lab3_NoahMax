/******************************************************************************
 * File: sprites.c
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
     {TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, RD, RD, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, RD, RD, TR, TR, TR, TR},
     {TR, TR, TR, TR, RD, RD, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, RD, RD, TR, TR, TR, TR},
     {TR, TR, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, TR, TR},
     {TR, TR, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, TR, TR},
     {TR, TR, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, TR, TR},
     {TR, TR, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, TR, TR},
     {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
     {TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR},
     {TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, RD, RD, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, RD, RD, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR},
     {TR, TR, TR, TR, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR},
     {TR, TR, TR, TR, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR},
     {TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR},
     {TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR},
     {TR, TR, TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR}
 };
 
  // Second Goomba Animation Frame
 const uint16_t goombaframe2[GOOMBA_SIZE][GOOMBA_SIZE] = {
     {TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, RD, RD, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, RD, RD, TR, TR, TR, TR},
     {TR, TR, TR, TR, RD, RD, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, RD, RD, TR, TR, TR, TR},
     {TR, TR, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, TR, TR},
     {TR, TR, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, TR, TR},
     {TR, TR, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, TR, TR},
     {TR, TR, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, TR, TR},
     {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, WT, WT, BL, BL, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
     {TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR},
     {TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, RD, RD, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, RD, RD, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, TR, TR, TR, TR},
     {TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, TR, TR, TR, TR},
     {TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR},
     {TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR},
     {TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR, TR, TR},
 };
 
  // Goomba Dead Sprite
 const uint16_t goomba_dead[GOOMBA_DEAD_H][GOOMBA_DEAD_W] = {
     {TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR},
     {TR, TR, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, TR, TR},
     {TR, TR, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, TR, TR},
     {RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, WT, WT, BL, BL, BL, BL, BL, BL, WT, WT, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD},
     {RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, WT, WT, BL, BL, BL, BL, BL, BL, WT, WT, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
     {TR, TR, TR, TR, TR, TR, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR},
     {TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR},
 };
 
 // Goomba Dead Sprite
 const uint16_t goomba_dead_flipped[GOOMBA_DEAD_H][GOOMBA_DEAD_W] = {
     {TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR},
     {TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, TR, TR, TR, TR, TR, TR},
     {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD},
     {RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, WT, WT, BL, BL, BL, BL, BL, BL, WT, WT, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD},
     {RD, RD, RD, RD, WT, WT, WT, WT, WT, WT, WT, WT, BL, BL, BL, BL, BL, BL, WT, WT, WT, WT, WT, WT, WT, WT, RD, RD, RD, RD},
     {TR, TR, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, TR, TR},
     {TR, TR, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, BL, BL, RD, RD, RD, RD, TR, TR},
     {TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
 };
 
 // Coin Sprite 
 const uint16_t coin_sprite[COIN_H][COIN_W] = {
     {TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR},
     {TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR},
     {TR, TR, BL, BL, WT, WT, WT, WT, WT, WT, WT, BL, BL, TR, TR},
     {TR, TR, BL, BL, YL, YL, YL, YL, YL, YL, YL, BL, BL, TR, TR},
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
     {TR, TR, BL, BL, YL, YL, YL, YL, YL, YL, YL, BL, BL, TR, TR},
     {TR, TR, BL, BL, YL, YL, YL, DO, DO, DO, DO, BL, BL, TR, TR},
     {TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR},
     {TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR},
 };
 
 // Mario base sprite (standing around) (WIP)
 const uint16_t mario_base[MARIO_H][MARIO_W] = {
    {TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
    {TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
    {TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR},
    {TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR},
    {TR, TR, TR, TR, TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, LO, LO, TR, TR, TR, TR, TR, TR, TR, TR},
    {TR, TR, TR, TR, TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, LO, LO, TR, TR, TR, TR, TR, TR, TR, TR},
    {TR, TR, TR, TR, TR, TR, BL, BL, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, TR, TR, TR, TR, TR},
    {TR, TR, TR, TR, TR, TR, BL, BL, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, TR, TR, TR, TR, TR},
    {TR, TR, TR, TR, TR, TR, BL, BL, LO, LO, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, LO, TR},
    {TR, TR, TR, TR, TR, TR, BL, BL, LO, LO, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, LO, TR},
    {TR, TR, TR, TR, TR, TR, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR, TR},
    {TR, TR, TR, TR, TR, TR, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR, TR},
    {TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, TR, TR, TR, TR, TR, TR, TR},
    {TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, TR, TR, TR, TR, TR, TR, TR},
    {TR, TR, TR, TR, TR, TR, TR, TR, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
    {TR, TR, TR, TR, TR, TR, TR, TR, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
    {TR, TR, TR, TR, TR, TR, DB, DB, DB, DB, DB, DB, DB, DB, RD, RD, DB, DB, DB, DB, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
    {TR, TR, TR, TR, TR, TR, DB, DB, DB, DB, DB, DB, DB, DB, RD, RD, DB, DB, RD, RD, DB, DB, DB, DB, DB, TR, TR, TR, TR, TR},
    {TR, TR, TR, TR, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, RD, RD, RD, RD, RD, RD, DB, DB, DB, DB, DB, DB, DB, TR, TR, TR},
    {TR, TR, TR, TR, DB, DB, DB, DB, DB, DB, DB, DB, DB, DB, RD, RD, RD, RD, RD, RD, DB, DB, DB, DB, DB, DB, DB, TR, TR, TR},
    {TR, TR, TR, TR, LO, LO, LO, LO, LO, LO, DB, DB, RD, RD, LO, LO, RD, RD, LO, LO, RD, RD, DB, DB, LO, LO, LO, LO, TR, TR},
    {TR, TR, TR, TR, LO, LO, LO, LO, LO, LO, DB, DB, RD, RD, LO, LO, RD, RD, LO, LO, RD, RD, DB, DB, LO, LO, LO, LO, TR, TR},
    {TR, TR, TR, TR, LO, LO, LO, LO, LO, LO, LO, LO, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LO, LO, LO, LO, LO, LO, TR, TR},
    {TR, TR, TR, TR, LO, LO, LO, LO, LO, LO, LO, LO, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LO, LO, LO, LO, LO, LO, TR, TR},
    {TR, TR, TR, TR, LO, LO, LO, LO, LO, LO, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LO, LO, LO, LO, TR, TR},
    {TR, TR, TR, TR, LO, LO, LO, LO, LO, LO, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, LO, LO, LO, LO, TR, TR},
    {TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR},
    {TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR},
    {TR, TR, TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR},
    {TR, TR, TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR},
    {TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL},
    {TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL},
};

 
 const uint16_t mario_run1[MARIO_H][MARIO_W] = {
     {TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, LO, LO, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, BL, BL, BL, BL, BL, BL, LO, LO, LO, LO, BL, BL, LO, LO, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, BL, BL, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, BL, BL, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, BL, BL, LO, LO, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, LO, TR},
     {TR, TR, TR, TR, TR, TR, BL, BL, LO, LO, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, BL, BL, LO, LO, LO, LO, LO, LO, LO, TR},
     {TR, TR, TR, TR, TR, TR, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, BL, BL, BL, BL, LO, LO, LO, LO, LO, LO, LO, LO, BL, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, LO, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, DB, DB, RD, RD, RD, RD, DB, DB, DB, DB, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, DB, DB, RD, RD, RD, RD, DB, DB, DB, DB, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, TR, DB, DB, DB, DB, DB, DB, DB, DB, RD, RD, RD, RD, RD, RD, DB, DB, DB, DB, DB, DB, LO, LO, LO, LO, LO, TR},
     {TR, TR, TR, TR, DB, DB, DB, DB, DB, DB, DB, DB, RD, RD, RD, RD, RD, RD, DB, DB, DB, DB, DB, DB, LO, LO, LO, LO, LO, TR},
     {TR, LO, LO, LO, DB, DB, DB, DB, DB, DB, DB, DB, RD, RD, LO, LO, RD, RD, RD, RD, RD, RD, DB, DB, DB, DB, LO, LO, LO, TR},
     {TR, LO, LO, LO, DB, DB, DB, DB, DB, DB, DB, DB, RD, RD, LO, LO, RD, RD, RD, RD, RD, RD, DB, DB, DB, DB, LO, LO, LO, TR},
     {TR, LO, LO, LO, LO, LO, TR, TR, DB, DB, DB, DB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, BL, BL, TR, TR},
     {TR, LO, LO, LO, LO, LO, TR, TR, DB, DB, DB, DB, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, BL, BL, TR, TR},
     {TR, LO, LO, LO, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, TR, TR, BL, BL, BL, BL, TR, TR},
     {TR, LO, LO, LO, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, TR, TR},
     {TR, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, TR, TR},
     {TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, TR, TR},
     {TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, RD, TR, TR, TR, TR, TR, TR, RD, RD, RD, RD, RD, RD, BL, BL, BL, BL, TR, TR},
     {TR, TR, TR, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
     {TR, TR, TR, BL, BL, BL, BL, BL, BL, BL, BL, BL, BL, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR, TR},
 };
 
 //─── draw-functions ────────────────────────────────────────────────────
 
 void DrawSprite(short x0, short y0, const uint16_t *sprite, short w, short h) {
     for (short row = 0; row < h; row++) {
         for (short col = 0; col < w; col++) {
             // load the color from the flat array
             uint16_t c = sprite[row * w + col];
             if (c == TR) continue; 
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
 
 void drawMarioBase(short x, short y) {
     DrawSprite(x, y, &mario_base[0][0], MARIO_W, MARIO_H);
 }
 
 void drawMarioRun1(short x, short y) {
     DrawSprite(x, y, &mario_run1[0][0], MARIO_W, MARIO_H);
 }