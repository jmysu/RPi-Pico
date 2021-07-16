# Party Time, Arms! [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)<br>
### Interesting projects based on RPi-Pico  _(Work-in-Progress)_<br>
 
An UNO bread-board w/ RPi-Pico, Arduino-Nano, Adafruit QtPy, SEEED Xiao!
With some added features:
 - Neopixel RGB LEDs.
 - Shared I2C, SPI, UART, A/D & SD card.
 - 5V/3V3 power source selectable.
 - SPI LCD interface w/ touch.
 - Arduino-Uno/Mega compatible size/Holes.<br>
   <img src="pic/UnoPicoQ.gif" width=640><br>

<img src="pic/UnoPicoNanoQ_Top.png" width=400><img src="pic/UnoPicoNanoQ_Btm.png" width=400> <br>
<img src="pic/UnoPicoNanoQ_Pico.png" width=400><img src="pic/UnoPicoNanoQ_PicoNano.png" width=400>(w/ Nano)<br>
<img src="pic/UnoPicoNanoQ_PicoQ.png" width=400>(w/ QtPy or Xiao)<br>
<br>
<br>

Fritzing part made by Eagle2Fritzing:<br>
Parts located at here:(https://github.com/jmysu/RPi-Pico/tree/main/hardware/Fritzing/FritzingUnoPico/bins)<br>
<img src="pic/UnoPicoFritz0207.png" width=640> <br><br>

<br>
RPi_Pico Pinout from (https://www.raspberrypi.org/documentation/pico/getting-started/)
<img src="pic/RPi_PicoPinout_R3.jpg" width=640>
<br>
<br>
### Pico Pinout Terminal Diagram ### 
curl https://gabmus.org/pico_pinout
Raspberry Pi Pico pinout diagram
Raspberry Pi Pico pinout diagram

                                              ┌╌ [92mLED (GP25)[39m
                                              ┆ ┏━━━━┓          
                                          ┌─────┃    ┃─────┐
[34mUART0 TX[39m | [36mI2C0 SDA[39m | [35mSPI0 RX[39m  | [92mGP0[39m  | 01│●  ┆ ┗━━━━┛    ●│40 | [31mVBUS[39m
[34mUART0 RX[39m | [36mI2C0 SCL[39m | [35mSPI0 CSn[39m | [92mGP1[39m  | 02│●  ⏄           ●│39 | [31mVSYS[39m
                                 [37mGND[39m  | 03│■              ■│38 | [37mGND[39m
           [36mI2C1 SDA[39m | [35mSPI0 SCK[39m | [92mGP2[39m  | 04│●    ╭─╮       ●│37 | [91m3V3_EN[39m
           [36mI2C1 SCL[39m | [35mSPI0 TX[39m  | [92mGP3[39m  | 05│●    │ │       ●│36 | [31m3V3(OUT)[39m
[94mUART1 TX[39m | [36mI2C0 SDA[39m | [35mSPI0 RX[39m  | [92mGP4[39m  | 06│●    ╰─╯       ●│35 |          | [32mADC_VREF[39m
[94mUART1 RX[39m | [36mI2C0 SCL[39m | [35mSPI0 CSn[39m | [92mGP5[39m  | 07│●              ●│34 | [92mGP28[39m     | [32mADC2[39m
                                 [37mGND[39m  | 08│■              ■│33 | [37mGND[39m      | [32mAGND[39m
           [36mI2C1 SDA[39m | [35mSPI0 SCK[39m | [92mGP6[39m  | 09│●   ┌─────┐    ●│32 | [92mGP27[39m     | [32mADC1[39m     | [36mI2C1 SCL[39m
           [36mI2C1 SCL[39m | [35mSPI0 TX[39m  | [92mGP7[39m  | 10│●   │     │    ●│31 | [92mGP26[39m     | [32mADC0[39m     | [36mI2C1 SDA[39m
[94mUART1 TX[39m | [36mI2C0 SDA[39m | [35mSPI1 RX[39m  | [92mGP8[39m  | 11│●   │     │    ●│30 | [91mRUN[39m
[94mUART1 RX[39m | [36mI2C0 SCL[39m | [35mSPI1 CSn[39m | [92mGP9[39m  | 12│●   └─────┘    ●│29 | [92mGP22
                                 [37mGND[39m  | 13│■              ■│28 | [37mGND[39m
           [36mI2C1 SDA[39m | [35mSPI1 SCK[39m | [92mGP10[39m | 14│●              ●│27 | [92mGP21[39m     |          | [36mI2C0 SCL[39m
           [36mI2C1 SCL[39m | [35mSPI1 TX[39m  | [92mGP11[39m | 15│●              ●│26 | [92mGP20[39m     |          | [36mI2C0 SDA[39m
[94mUART0 TX[39m | [36mI2C0 SDA[39m | [35mSPI1 RX[39m  | [92mGP12[39m | 16│●              ●│25 | [92mGP19[39m     | [35mSPI0 TX[39m  | [36mI2C1 SCL[39m
[94mUART0 RX[39m | [36mI2C0 SCL[39m | [35mSPI1 CSn[39m | [92mGP13[39m | 17│●              ●│24 | [92mGP18[39m     | [35mSPI0 SCK[39m | [36mI2C1 SDA[39m
                                 [37mGND[39m  | 18│■              ■│23 | [37mGND[39m
           [36mI2C1 SDA[39m | [35mSPI1 SCK[39m | [92mGP14[39m | 19│●              ●│22 | [92mGP17[39m     | [35mSPI0 CSn[39m | [36mI2C0 SCL[39m | [94mUART0 RX[39m
           [36mI2C1 SCL[39m | [35mSPI1 TX[39m  | [92mGP15[39m | 20│●     ● ■ ●    ●│21 | [92mGP16[39m     | [35mSPI0 RX[39m  | [36mI2C0 SDA[39m | [94mUART0 TX[39m
                                          └────────────────┘
                                                 ┆ ┆ ┆
                                                 ┆ ┆ └╌ [33mSWDIO[39m
                                                 ┆ └╌╌╌ [37mGND[39m
                                                 └╌╌╌╌╌ [33mSWCLK[39m

[31mPower[39m
[37mGround[39m
[34mUART[39m
[92mGPIO, PIO, PWM[39m
[32mADC[39m
[35mSPI[39m
[36mI2C[39m
[91mSystem Control[39m
[33mDebugging[39m
<br>                        
<br>

Zoomable RP2040 top layer:
https://siliconpr0n.org/map/raspberry-pi/rp2-b0/mz_mit20x/ <br>

RP2040 chip teardown:
https://buzzchronicles.com/Mollyycolllinss/b/tech/10662/ <br>

Another inside description posted at [Tiny Transistors](https://www.tinytransistors.net/2021/01/27/raspberry-pi-pico/) <br>
<img src="pic/RP2040-die-shot.jpg" width=640>

<br>
<br>
<br>

## References <br>
  -[RPi_Pico](https://www.raspberrypi.org/documentation/pico/getting-started/) Pico Getting Started!<br>
  -[Arduino RP2040 Connect](https://blog.arduino.cc/2021/01/20/welcome-raspberry-pi-to-the-world-of-microcontrollers/) Arduino board for RP2040.<br>
  -[Adafruit QtPy](https://www.adafruit.com/qtpy) Another SAMD21 dev. board.<br>
  -[Eagle2Fritzing](https://github.com/squix78/eagle2fritzing-parent) A nice tool converts Eagle .brd to Fritzing part.<br> 

