/*******************************************************************************
 * controls.c
 *
 * Authors: Max Warner (mtw82), Noah Wilson (njw66)
 *
 * Description:
 *   Button control implementation for setup and polling in our ECE 4760 Final
 *   Project, a Super Mario Bros–inspired game.
 *
 ******************************************************************************/

#include "controls.h"
#include "pico/stdlib.h"
#include "vga16_graphics.h"    // for fillRect, SCREEN_W, SCREEN_H
#include "colors.h"            // for a BLUE constant, e.g. LB or DB

void controls_init(void) {
    // list out your pins
    const uint pins[] = { LEFT_PIN, JUMP_PIN, RIGHT_PIN, RESET_PIN };
    const size_t npins = sizeof(pins) / sizeof(pins[0]);
    for (size_t i = 0; i < npins; i++) {
        gpio_init(pins[i]);
        gpio_set_dir(pins[i], GPIO_IN);
        gpio_pull_up(pins[i]);
    }
}

bool reset_pressed(void) {
    // active-high button: gpio_get() returns 1 when pressed
    return gpio_get(RESET_PIN) == 1;
}

bool right_pressed(void) {
    return gpio_get(RIGHT_PIN) == 1;
}

bool left_pressed(void) {
    return gpio_get(LEFT_PIN) == 1;
}

bool jump_pressed(void) {
    return gpio_get(JUMP_PIN) == 1;
}
