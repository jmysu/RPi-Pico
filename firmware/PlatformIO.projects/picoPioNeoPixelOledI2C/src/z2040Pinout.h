
/*
Raspberry Pi Pico pinout diagram

                                              ┌╌ LED (GP25)
                                              ┆ ┏━━━━┓          
                                          ┌─────┃    ┃─────┐
UART0 TX | I2C0 SDA | SPI0 RX  | GP0  | 01│●  ┆ ┗━━━━┛    ●│40 | VBUS
UART0 RX | I2C0 SCL | SPI0 CSn | GP1  | 02│●  ⏄           ●│39 | VSYS
                                 GND  | 03│■              ■│38 | GND
           I2C1 SDA | SPI0 SCK | GP2  | 04│●    ╭─╮       ●│37 | 3V3_EN
           I2C1 SCL | SPI0 TX  | GP3  | 05│●    │ │       ●│36 | 3V3(OUT)
UART1 TX | I2C0 SDA | SPI0 RX  | GP4  | 06│●    ╰─╯       ●│35 |          | ADC_VREF
UART1 RX | I2C0 SCL | SPI0 CSn | GP5  | 07│●              ●│34 | GP28     | ADC2
                                 GND  | 08│■              ■│33 | GND      | AGND
           I2C1 SDA | SPI0 SCK | GP6  | 09│●   ┌─────┐    ●│32 | GP27     | ADC1     | I2C1 SCL
           I2C1 SCL | SPI0 TX  | GP7  | 10│●   │     │    ●│31 | GP26     | ADC0     | I2C1 SDA
UART1 TX | I2C0 SDA | SPI1 RX  | GP8  | 11│●   │     │    ●│30 | RUN
UART1 RX | I2C0 SCL | SPI1 CSn | GP9  | 12│●   └─────┘    ●│29 | GP22
                                 GND  | 13│■              ■│28 | GND
           I2C1 SDA | SPI1 SCK | GP10 | 14│●              ●│27 | GP21     |          | I2C0 SCL
           I2C1 SCL | SPI1 TX  | GP11 | 15│●              ●│26 | GP20     |          | I2C0 SDA
UART0 TX | I2C0 SDA | SPI1 RX  | GP12 | 16│●              ●│25 | GP19     | SPI0 TX  | I2C1 SCL
UART0 RX | I2C0 SCL | SPI1 CSn | GP13 | 17│●              ●│24 | GP18     | SPI0 SCK | I2C1 SDA
                                 GND  | 18│■              ■│23 | GND
           I2C1 SDA | SPI1 SCK | GP14 | 19│●              ●│22 | GP17     | SPI0 CSn | I2C0 SCL | UART0 RX
           I2C1 SCL | SPI1 TX  | GP15 | 20│●     ● ■ ●    ●│21 | GP16     | SPI0 RX  | I2C0 SDA | UART0 TX
                                          └────────────────┘
                                                 ┆ ┆ ┆
                                                 ┆ ┆ └╌ SWDIO
                                                 ┆ └╌╌╌ GND
                                                 └╌╌╌╌╌ SWCLK



*/
/** \file gpio.h
 *  \defgroup hardware_gpio hardware_gpio
 *
 * General Purpose Input/Output (GPIO) API
 *
 * RP2040 has 36 multi-functional General Purpose Input / Output (GPIO) pins, divided into two banks. In a typical use case,
 * the pins in the QSPI bank (QSPI_SS, QSPI_SCLK and QSPI_SD0 to QSPI_SD3) are used to execute code from an external
 * flash device, leaving the User bank (GPIO0 to GPIO29) for the programmer to use. All GPIOs support digital input and
 * output, but GPIO26 to GPIO29 can also be used as inputs to the chip’s Analogue to Digital Converter (ADC). Each GPIO
 * can be controlled directly by software running on the processors, or by a number of other functional blocks.
 *
 * The function allocated to each GPIO is selected by calling the \ref gpio_set_function function. \note Not all functions
 * are available on all pins.
 *
 * Each GPIO can have one function selected at a time. Likewise, each peripheral input (e.g. UART0 RX) should only be selected on
 * one _GPIO_ at a time. If the same peripheral input is connected to multiple GPIOs, the peripheral sees the logical OR of these
 * GPIO inputs. Please refer to the datasheet for more information on GPIO function select.
 *
 * ### Function Select Table
 *
 *  GPIO   | F1       | F2        | F3       | F4     | F5  | F6   | F7   | F8            | F9
 *  -------|----------|-----------|----------|--------|-----|------|------|---------------|----
 *  0      | SPI0 RX  | UART0 TX  | I2C0 SDA | PWM0 A | SIO | PIO0 | PIO1 |               | USB OVCUR DET
 *  1      | SPI0 CSn | UART0 RX  | I2C0 SCL | PWM0 B | SIO | PIO0 | PIO1 |               | USB VBUS DET
 *  2      | SPI0 SCK | UART0 CTS | I2C1 SDA | PWM1 A | SIO | PIO0 | PIO1 |               | USB VBUS EN
 *  3      | SPI0 TX  | UART0 RTS | I2C1 SCL | PWM1 B | SIO | PIO0 | PIO1 |               | USB OVCUR DET
 * 
 *  4      | SPI0 RX  | UART1 TX  | I2C0 SDA | PWM2 A | SIO | PIO0 | PIO1 |               | USB VBUS DET
 *  5      | SPI0 CSn | UART1 RX  | I2C0 SCL | PWM2 B | SIO | PIO0 | PIO1 |               | USB VBUS EN
 *  6      | SPI0 SCK | UART1 CTS | I2C1 SDA | PWM3 A | SIO | PIO0 | PIO1 |               | USB OVCUR DET
 *  7      | SPI0 TX  | UART1 RTS | I2C1 SCL | PWM3 B | SIO | PIO0 | PIO1 |               | USB VBUS DET
 
 *  8      | SPI1 RX  | UART1 TX  | I2C0 SDA | PWM4 A | SIO | PIO0 | PIO1 |               | USB VBUS EN
 *  9      | SPI1 CSn | UART1 RX  | I2C0 SCL | PWM4 B | SIO | PIO0 | PIO1 |               | USB OVCUR DET
 *  10     | SPI1 SCK | UART1 CTS | I2C1 SDA | PWM5 A | SIO | PIO0 | PIO1 |               | USB VBUS DET
 *  11     | SPI1 TX  | UART1 RTS | I2C1 SCL | PWM5 B | SIO | PIO0 | PIO1 |               | USB VBUS EN
 
 *  12     | SPI1 RX  | UART0 TX  | I2C0 SDA | PWM6 A | SIO | PIO0 | PIO1 |               | USB OVCUR DET
 *  13     | SPI1 CSn | UART0 RX  | I2C0 SCL | PWM6 B | SIO | PIO0 | PIO1 |               | USB VBUS DET
 *  14     | SPI1 SCK | UART0 CTS | I2C1 SDA | PWM7 A | SIO | PIO0 | PIO1 |               | USB VBUS EN
 *  15     | SPI1 TX  | UART0 RTS | I2C1 SCL | PWM7 B | SIO | PIO0 | PIO1 |               | USB OVCUR DET
 
 *  16     | SPI0 RX  | UART0 TX  | I2C0 SDA | PWM0 A | SIO | PIO0 | PIO1 |               | USB VBUS DET
 *  17     | SPI0 CSn | UART0 RX  | I2C0 SCL | PWM0 B | SIO | PIO0 | PIO1 |               | USB VBUS EN
 *  18     | SPI0 SCK | UART0 CTS | I2C1 SDA | PWM1 A | SIO | PIO0 | PIO1 |               | USB OVCUR DET
 *  19     | SPI0 TX  | UART0 RTS | I2C1 SCL | PWM1 B | SIO | PIO0 | PIO1 |               | USB VBUS DET
 
 *  20     | SPI0 RX  | UART1 TX  | I2C0 SDA | PWM2 A | SIO | PIO0 | PIO1 | CLOCK GPIN0   | USB VBUS EN
 *  21     | SPI0 CSn | UART1 RX  | I2C0 SCL | PWM2 B | SIO | PIO0 | PIO1 | CLOCK GPOUT0  | USB OVCUR DET
 *  22     | SPI0 SCK | UART1 CTS | I2C1 SDA | PWM3 A | SIO | PIO0 | PIO1 | CLOCK GPIN1   | USB VBUS DET
 *  23     | SPI0 TX  | UART1 RTS | I2C1 SCL | PWM3 B | SIO | PIO0 | PIO1 | CLOCK GPOUT1  | USB VBUS EN
 
 *  24     | SPI1 RX  | UART1 TX  | I2C0 SDA | PWM4 A | SIO | PIO0 | PIO1 | CLOCK GPOUT2  | USB OVCUR DET
 *  25     | SPI1 CSn | UART1 RX  | I2C0 SCL | PWM4 B | SIO | PIO0 | PIO1 | CLOCK GPOUT3  | USB VBUS DET
 *  26     | SPI1 SCK | UART1 CTS | I2C1 SDA | PWM5 A | SIO | PIO0 | PIO1 |               | USB VBUS EN
 *  27     | SPI1 TX  | UART1 RTS | I2C1 SCL | PWM5 B | SIO | PIO0 | PIO1 |               | USB OVCUR DET
 
 *  28     | SPI1 RX  | UART0 TX  | I2C0 SDA | PWM6 A | SIO | PIO0 | PIO1 |               | USB VBUS DET
 *  29     | SPI1 CSn | UART0 RX  | I2C0 SCL | PWM6 B | SIO | PIO0 | PIO1 |               | USB VBUS EN

 */
/*
Zero2040 pinout
Raspberry Pi Pico pinout diagram

                                              ┌╌ LED/WS8212 (GP25)
                                              ┆ ┏━━━━┓          
                                          ┌─────┃    ┃─────┐
                      UART0 TX | GP0  | 01│●  ┆ ┗━━━━┛    ●│40 | VBUS
                      UART0 RX | GP1  | 02│●  ⏄          ●│39 | VSYS
                                 GND  | 03│■              ■│38 | GND
                                 GP2  | 04│●    ╭─╮       ●│37 | 3V3_EN
                                 GP3  | 05│●    │ │       ●│36 | 3V3(OUT)
                      I2C0 SDA | GP4  | 06│●    ╰─╯       ●│35 |          | ADC_VREF
                      I2C0 SCL | GP5  | 07│●              ●│34 | GP28     | ADC2
                                 GND  | 08│■              ■│33 | GND      | AGND
                                 GP6  | 09│●   ┌─────┐    ●│32 | GP27     | ADC1      
                                 GP7  | 10│●   │     │    ●│31 | GP26     | ADC0      
                      UART1 TX | GP8  | 11│●   │     │    ●│30 | RUN
                      UART1 RX | GP9  | 12│●   └─────┘    ●│29 | GP22
                                 GND  | 13│■              ■│28 | GND
                                 GP10 | 14│●              ●│27 | GP21      
                                 GP11 | 15│●              ●│26 | GP20      
                      SPI1 RX  | GP12 | 16│●              ●│25 | GP19     | SPI0 TX  
                      SPI1 CSn | GP13 | 17│●              ●│24 | GP18     | SPI0 SCK 
                                 GND  | 18│■              ■│23 | GND
                      SPI1 SCK | GP14 | 19│●              ●│22 | GP17     | SPI0 CSn
                      SPI1 TX  | GP15 | 20│●     ● ■ ●    ●│21 | GP16     | SPI0 RX  
                                          └────────────────┘
                                                 ┆ ┆ ┆
                                                 ┆ ┆ └╌ SWDIO
                                                 ┆ └╌╌╌ GND
                                                 └╌╌╌╌╌ SWCLK

*/
//User Friendly Port Name   GP
//----------------------------
#define Z2040_UART0_TX      0
#define Z2040_UART0_RX      1

#define Z2040_I2C1_SDA      2
#define Z2040_I2C1_SCL      3
#define Z2040_I2C0_SDA      4
#define Z2040_I2C0_SCL      5
#define PicoMate090j_I2C0_SDA      20
#define PicoMate090j_I2C0_SCL      21

#define Z2040_SPI1_SDI      12
#define Z2040_SPI1_SS       13
#define Z2040_SPI1_SCK      14
#define Z2040_SPI1_SDO      15

#define Z2040_SPI0_SDI      16
#define Z2040_SPI0_SS       17
#define Z2040_SPI0_SCK      18
#define Z2040_SPI0_SDO      19

#define Z2040_UART1_TX      20
#define Z2040_UART1_RX      21

#define Z2040_AD0           26
#define Z2040_AD1           27
#define Z2040_AD2           28
//----------------------------


