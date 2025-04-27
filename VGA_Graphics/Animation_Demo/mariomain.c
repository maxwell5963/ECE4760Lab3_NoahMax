#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "vga16_graphics.h"

// GPIO pins for controls
#define LEFT_BUTTON_PIN 20
#define RIGHT_BUTTON_PIN 21
#define JUMP_BUTTON_PIN 19

// Simple character position
static int characterX = 0;
static int characterY = 180;

// Initialize GPIO pins
void initGPIO(void) {
    // Initialize control buttons
    gpio_init(LEFT_BUTTON_PIN);
    gpio_init(RIGHT_BUTTON_PIN);
    gpio_init(JUMP_BUTTON_PIN);
    
    // Set button pins as inputs with pull-up resistors
    gpio_set_dir(LEFT_BUTTON_PIN, GPIO_IN);
    gpio_set_dir(RIGHT_BUTTON_PIN, GPIO_IN);
    gpio_set_dir(JUMP_BUTTON_PIN, GPIO_IN);
    
    gpio_pull_up(LEFT_BUTTON_PIN);
    gpio_pull_up(RIGHT_BUTTON_PIN);
    gpio_pull_up(JUMP_BUTTON_PIN);
    
    // Initialize reset button
    initResetButton();
}

int main() {
    // Initialize stdio
    stdio_init_all();
    
    // Initialize GPIO
    initGPIO();
    
    // Main game loop
    while (true) {
        // Check reset button
        if (isResetButtonPressed()) {
            if (isGameReset()) {
                startGame();  // Start the game if in reset state
                characterX = 0;
                characterY = 180;
            } else {
                resetGameState();  // Reset the game if running
            }
            sleep_ms(200);  // Debounce delay
        }
        
        // Only update game if it's running
        if (isGameRunning()) {
            // Simple character control
            if (!gpio_get(LEFT_BUTTON_PIN)) {
                characterX -= 2;
            }
            if (!gpio_get(RIGHT_BUTTON_PIN)) {
                characterX += 2;
            }
            if (!gpio_get(JUMP_BUTTON_PIN)) {
                // Simple jump effect
                characterY -= 10;
            } else if (characterY < 180) {
                // Simple gravity
                characterY += 5;
            }
            
            // Ensure character stays on ground
            if (characterY > 180) {
                characterY = 180;
            }
            
            // Draw the background based on character position
            drawBackground(characterX);
            
            // Draw a simple square for the character (at fixed screen position)
            fillRect(150, characterY, 16, 16, 12); // Red square for character
        }
        
        // Maintain frame rate
        sleep_ms(16);  // Approximately 60 FPS
    }
    
    return 0;
}