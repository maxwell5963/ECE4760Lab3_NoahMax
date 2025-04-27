/******************************************************************************
 * File: colors.h
 * 
 * Authors: Max Warner (mtw82), Noah Wilson (njw66)
 *
 * Description:
 *    This file is our shorthand macros for colord definitions (makes arrays
      ( a lot cleaner).
 ******************************************************************************/

 #ifndef COLORS_H
 #define COLORS_H
 
 #include "vga16_graphics.h"   // defines BLACK, DARK_GREEN, MED_GREEN, GREEN, etc.
 
 // shorthand names:
 #define BL   BLACK        // 0
 #define DG   DARK_GREEN   // 1
 #define GR   MED_GREEN     // 2
 #define LG   GREEN         // 3
 #define DB   DARK_BLUE    // 4
 #define LB   BLUE         // 5
 #define OB   LIGHT_BLUE   // 6
 #define CY   CYAN         // 7
 #define RD   RED          // 8
 #define DO   DARK_ORANGE  // 9
 #define LO   ORANGE        // 10
 #define YL   YELLOW       // 11
 #define MG   MAGENTA      // 12
 #define PK   PINK         // 13
 #define LP   LIGHT_PINK   // 14
 #define WT   WHITE        // 15

 #define TR   CY            // transparent
 
 #endif // COLORS_H
 