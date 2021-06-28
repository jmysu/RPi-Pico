#include <Arduino.h>

#include "boards/pico.h"
#include "hardware/pio.h"
#include "pwm.pio.h"
#include "ws2812_pio.h"

// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 28  //Pico AD2

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 2  // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 100  // Time (in milliseconds) to pause between pixels

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

void setup() {
    // setup WS2812 PIO
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    // 800kHz, 8 bit transfers
    ws2812_program_init(pio, sm, offset, PIN, 800000, 8);
    // setup pwm PIO
    uint offset1 = pio_add_program(pio, &pwm_program);
    pwm_program_init(pio, 1, offset1, LED_BUILTIN);
    pio_pwm_set_period(pio, 1, (1u << 16) - 1);
}

int level = 0;
void loop() {
    for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
        for (int i = 0; i < pixels.numPixels(); i++) {  // For each pixel in strip...
            int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
            pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
        }
        pixels.show();  // Update strip with new contents
        delay(5);       // Pause for a moment

        //pwm_set_gpio_level(LED_BUILTIN, pixelHue>>16);
        level = (level + 1) % 256;
        pio_pwm_set_level(pio0, 1, level * level);
    }
}
