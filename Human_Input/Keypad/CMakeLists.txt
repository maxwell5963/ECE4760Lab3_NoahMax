add_executable(Keypad)

# must match with pio filename and executable name from above
pico_generate_pio_header(Keypad ${CMAKE_CURRENT_LIST_DIR}/hsync.pio)
pico_generate_pio_header(Keypad ${CMAKE_CURRENT_LIST_DIR}/vsync.pio)
pico_generate_pio_header(Keypad ${CMAKE_CURRENT_LIST_DIR}/rgb.pio)

# must match with executable name and source file names
target_sources(Keypad PRIVATE keypad.c vga16_graphics.c)

# must match with executable name
target_link_libraries(Keypad PRIVATE pico_stdlib pico_multicore hardware_pio hardware_dma hardware_sync hardware_spi)

# must match with executable name
pico_add_extra_outputs(Keypad)
