/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// Output PWM signals on pins 0 and 1

#include "boards/pico.h"
#include "stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

int setupPWM() {
    /// \tag::setup_pwm[]

    // Tell GPIO25 is allocated to the PWM
    gpio_set_function(25, GPIO_FUNC_PWM);
    //gpio_set_function(1, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to GPIO25 (it's slice 0)
    uint slice_num = pwm_gpio_to_slice_num(25);

    // Set period of 6 cycles (0 to 5 inclusive)
    pwm_set_wrap(slice_num, 5);
    // Set channel A output high for one cycle before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 2);
    // Set initial B output high for three cycles before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_B, 5);
    // Set the PWM running
    pwm_set_enabled(slice_num, true);
    /// \end::setup_pwm[]

    // Note we could also use pwm_set_gpio_level(gpio, x) which looks up the
    // correct slice and channel for a given GPIO.
}