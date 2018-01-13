David Robillard's Ergodox Layout
================================

A layout for the Ergodox EZ inspired by the Kinesis Advantage.
See [source](keymap.c) for documentation.

To build and install:

    cd /path/to/qmk_firmware/
    git clone git@github.com:drobilla/ergodox.git keyboards/ergodox_ez/keymaps/drobilla
    rm -f ergodox_ez_drobilla.hex
    make ergodox_ez:drobilla
    teensy_loader_cli -mmcu=atmega32u4 -w ergodox_ez_drobilla.hex

Then press the flash button on your keyboard.
