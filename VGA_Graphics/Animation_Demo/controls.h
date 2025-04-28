/*******************************************************************************
 * controls.h
 *
 * Authors: Max Warner (mtw82), Noah Wilson (njw66)
 *
 * Description:
 *   Button control setup and state-checking functions for movement and reset
 *   functionality in our ECE 4760 Final Project, a Super Mario Bros–inspired game.
 *
 ******************************************************************************/

#ifndef CONTROLS_H
#define CONTROLS_H

#include <stdbool.h>

#define LEFT_PIN 10
#define JUMP_PIN 11
#define RIGHT_PIN 12
#define RESET_PIN 13

/// call once at startup to configure your button-pins
void controls_init(void);

/// call regularly (e.g. each frame) to peek at buttons
/// returns true if the reset button is currently pressed
bool reset_pressed(void);
bool right_pressed(void);
bool left_pressed(void);
bool jump_pressed(void);

#endif // CONTROLS_H
