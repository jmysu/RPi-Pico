/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include "boards/pico.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "blink.pio.h"

void blink_pin_forever(PIO pio, uint sm, uint offset, uint pin, uint freq) {
    blink_program_init(pio, sm, offset, pin);
    pio_sm_set_enabled(pio, sm, true);

    //printf("Blinking pin %d at %d Hz\n", pin, freq);
    pio->txf[sm] = clock_get_hz(clk_sys) / 2 * freq;
}

int pioBlink() {
    //setup_default_uart();

    // todo get free sm
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &blink_program);
    //printf("Loaded program at %d\n", offset);
    
    blink_pin_forever(pio, 0, offset, PICO_DEFAULT_LED_PIN, 1); //state machine 0: 1Hz on Pin25
    //blink_pin_forever(pio, 1, offset, 13, 4);
    //blink_pin_forever(pio, 2, offset, 11, 1);

}


