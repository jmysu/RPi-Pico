/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "hardware/pio.h"
#include "hardware/gpio.h"
#include "hardware/interp.h"
#include "hardware/spi.h"
 
#include "hardware/clocks.h"

#include "st7789_lcd.pio.h"
#include "raspberry_256x256_rgb565.h"
//#include "JC256x256.h"
//#include "stars256x256.h"
//#include "jc256.h" 
#include "fkc256.h"

#include "ST7735_128x160.h"

#define IMAGE_SIZE 256
#define LOG_IMAGE_SIZE 8
/*
#define PIN_DIN 0
#define PIN_CLK 1
#define PIN_CS 2
#define PIN_DC 3
#define PIN_RESET 4
#define PIN_BL 5
*/
//#define PicoKitB7789
#ifdef PicoKitB7789
//ST7789 240x240
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240
 //PicoKitB LCD Pin Define---
 #define PIN_BL    13
 #define PIN_RESET 12
 #define PIN_DIN   11
 #define PIN_CLK   10
 #define PIN_CS     9
 #define PIN_DC     8
#endif

//PyBase LCD PIN Define---
#define PyBASE7735
//ST7735 128x160

#ifdef PyBASE7735
 #define SCREEN_WIDTH 128
 #define SCREEN_HEIGHT 160

 #define PyBASE_RST  13
 #define PyBASE_CS    9
 #define PyBASE_DC   12
 #define PyBASE_MOSI 11 
 #define PyBASE_SCK  10

 #define PIN_RESET PyBASE_RST
 #define PIN_DIN   PyBASE_MOSI
 #define PIN_CLK   PyBASE_SCK
 #define PIN_CS    PyBASE_CS
 #define PIN_DC    PyBASE_DC
#endif

#define SERIAL_CLK_DIV 1.0f

// Format: cmd length (including cmd byte), post delay in units of 5 ms, then cmd payload
// Note the delays have been shortened a little
static const uint8_t st7789_init_seq[] = {
        1, 20, 0x01,                         // Software reset
        1, 10, 0x11,                         // Exit sleep mode
        2, 2, 0x3a, 0x55,                   // Set colour mode to 16 bit
        2, 0, 0x36, 0x00,                   // Set MADCTL: row then column, refresh is bottom to top ????
        5, 0, 0x2a, 0x00, 0x00, 0x00, 0xf0, // CASET: column addresses from 0 to 240 (f0)
        5, 0, 0x2b, 0x00, 0x00, 0x00, 0xf0, // RASET: row addresses from 0 to 240 (f0)
        1, 2, 0x21,                         // Inversion on, then 10 ms delay (supposedly a hack?)
        1, 2, 0x13,                         // Normal display on, then 10 ms delay
        1, 100, 0x29,                         // Main screen turn on, then wait 500 ms
        0                                     // Terminate list
};

static inline void lcd_set_dc_cs(bool dc, bool cs) {
    sleep_us(100);
    gpio_put_masked((1u << PIN_DC) | (1u << PIN_CS), !!dc << PIN_DC | !!cs << PIN_CS);
    sleep_us(100);
}

static inline void lcd_write_cmd(PIO pio, uint sm, const uint8_t *cmd, size_t count) {
    st7789_lcd_wait_idle(pio, sm);
    lcd_set_dc_cs(0, 0);
    st7789_lcd_put(pio, sm, *cmd++);
    if (count >= 2) {
        st7789_lcd_wait_idle(pio, sm);
        lcd_set_dc_cs(1, 0);
        for (size_t i = 0; i < count - 1; ++i)
            st7789_lcd_put(pio, sm, *cmd++);
    }
    st7789_lcd_wait_idle(pio, sm);
    lcd_set_dc_cs(1, 1);
}

static inline void lcd_init(PIO pio, uint sm, const uint8_t *init_seq) {
    const uint8_t *cmd = init_seq;
    while (*cmd) {
        lcd_write_cmd(pio, sm, cmd + 2, *cmd);
        sleep_ms(*(cmd + 1) * 5);
        cmd += *cmd + 2;
    }
}

static inline void st7789_start_pixels(PIO pio, uint sm) {
    uint8_t cmd = 0x2c; // RAMWR
    lcd_write_cmd(pio, sm, &cmd, 1);
    lcd_set_dc_cs(1, 0);
}

int pioLCD() {
    //stdio_init_all();

    PIO pio = pio0;
    uint sm = 0;
    uint offset = pio_add_program(pio, &st7789_lcd_program);

    st7789_lcd_program_init(pio, sm, offset, PIN_DIN, PIN_CLK, SERIAL_CLK_DIV);

    _gpio_init(PIN_CS);
    _gpio_init(PIN_DC);
    _gpio_init(PIN_RESET);

    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_set_dir(PIN_DC, GPIO_OUT);
    gpio_set_dir(PIN_RESET, GPIO_OUT);
    gpio_put(PIN_CS, 1);

    //Hardware LCD init! Important!!!
    gpio_put(PIN_RESET, 1);
    gpio_put(PIN_RESET, 0);
    sleep_ms(100);
    gpio_put(PIN_RESET, 1);
    
    #ifdef PyBASE7735
     lcd_init(pio, sm, st7735_initSeq);
    #else
     lcd_init(pio, sm, st7789_init_seq);
    #endif
    //gpio_put(PIN_BL, 1);


    // Other SDKs: static image on screen, lame, boring
    // Raspberry Pi Pico SDK: spinning image on screen, bold, exciting

    // Lane 0 will be u coords (bits 8:1 of addr offset), lane 1 will be v
    // coords (bits 16:9 of addr offset), and we'll represent coords with
    // 16.16 fixed point. ACCUM0,1 will contain current coord, BASE0/1 will
    // contain increment vector, and BASE2 will contain image base pointer
    
#define UNIT_LSB 16
    interp_config lane0_cfg = interp_default_config();
    // 0111 1111 1111 1111
    interp_config_set_shift(&lane0_cfg, UNIT_LSB - 1); // -1 because 2 bytes per pixel
    // 0000 0000 1111 1111
    interp_config_set_mask(&lane0_cfg, 1, 1 + (LOG_IMAGE_SIZE - 1)); // mask 1~8
    interp_config_set_add_raw(&lane0_cfg, true); // Add full accumulator to base with each POP

    interp_config lane1_cfg = interp_default_config();
    // 0000 0000 0000 0111
    interp_config_set_shift(&lane1_cfg, UNIT_LSB - (1 + LOG_IMAGE_SIZE)); //7
    // 1111 1111 0000 0000
    interp_config_set_mask(&lane1_cfg, 1 + LOG_IMAGE_SIZE, 1 + (2 * LOG_IMAGE_SIZE - 1)); //9~16
    interp_config_set_add_raw(&lane1_cfg, true);

    interp_set_config(interp0, 0, &lane0_cfg);
    interp_set_config(interp0, 1, &lane1_cfg);

    #ifdef PicoKitB7789
     interp0->base[2] = (uint32_t) raspberry_256x256;
    #endif
    #ifdef PyBASE7735
     //interp0->base[2] = (uint32_t) jc256x256;
     //interp0->base[2] = (uint32_t) stars_256x256;
     interp0->base[2] = (uint32_t) fkc256x256;
    #endif

    float theta = 0.f;
    float theta_max = 2.f * (float) M_PI;
    while (1) {
        theta += 0.02f;
        if (theta > theta_max) {
            theta -= theta_max;
            gpio_put(25, !gpio_get(25)); //toggling LED
            }
        int32_t rotate[4] = {
                cosf(theta) * (1 << UNIT_LSB), -sinf(theta) * (1 << UNIT_LSB),
                sinf(theta) * (1 << UNIT_LSB), cosf(theta) * (1 << UNIT_LSB)
        };
        interp0->base[0] = rotate[0]; //cosine X
        interp0->base[1] = rotate[2]; //sine Y
        st7789_start_pixels(pio, sm);
        for (int y = 0; y < SCREEN_HEIGHT; ++y) {
            interp0->accum[0] = rotate[1] * y * 2;
            interp0->accum[1] = rotate[3] * y / 2;
            for (int x = 0; x < SCREEN_WIDTH; ++x) {
                uint16_t colour = *(uint16_t *) (interp0->pop[2]);    
                // Swap Red and Blue (could check MADCTL setting to see if this is needed)
                //colour = (colour>>11) | (colour<<11) | (colour & 0x7E0);     
                st7789_lcd_put(pio, sm, (uint8_t)(colour >> 8));
                st7789_lcd_put(pio, sm, (uint8_t)(colour & 0xff)); 
            } 
        }  
    }
}
