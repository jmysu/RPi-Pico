/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "stdlib.h"
#include "hardware/pio.h"
#include "pwm.pio.h"
#include "boards/pico.h"

// Write `period` to the input shift register
void pio_pwm_set_period(PIO pio, uint sm, uint32_t period) {
    pio_sm_set_enabled(pio, sm, false);
    pio_sm_put_blocking(pio, sm, period);
    pio_sm_exec(pio, sm, pio_encode_pull(false, false));
    pio_sm_exec(pio, sm, pio_encode_out(pio_isr, 32));
    pio_sm_set_enabled(pio, sm, true);
}

// Write `level` to TX FIFO. State machine will copy this into X.
void pio_pwm_set_level(PIO pio, uint sm, uint32_t level) {
    pio_sm_put_blocking(pio, sm, level);
}

int pioPWM() {
    //stdio_init_all();
#ifndef PICO_DEFAULT_LED_PIN
#warning pio/pwm example requires a board with a regular LED
    //puts("Default LED pin was not defined");
#else

    // todo get free sm
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &pwm_program);
    //printf("Loaded program at %d\n", offset);

    pwm_program_init(pio, 0, offset, PICO_DEFAULT_LED_PIN);
    pio_pwm_set_period(pio, 0, (1u << 16) - 1);     //Pico DEFAULT GREEN LED

    pwm_program_init(pio, 1, offset, 18);           //PyBase RED LED
    pio_pwm_set_period(pio, 1, (1u << 15) - 1);
    pwm_program_init(pio, 2, offset, 19);           //PyBase ORANGER LED
    pio_pwm_set_period(pio, 2, (1u << 14) - 1);
    pwm_program_init(pio, 3, offset, 20);           //PyBase BLUE LED
    pio_pwm_set_period(pio, 3, (1u << 13) - 1);
    
    int level = 0;
    while (true) {
        //printf("Level = %d\n", level);
        pio_pwm_set_level(pio, 0, level * level);
        
        pio_pwm_set_level(pio, 1, level * level);
        pio_pwm_set_level(pio, 2, level * level);
        pio_pwm_set_level(pio, 3, level * level);
        
        level = (level + 1) % 256;
        sleep_ms(10);
    }
#endif
}
