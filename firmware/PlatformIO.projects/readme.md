
### PlatformIO.projects/testPico: Simple LED blinking for RPI-Pico Arduino w/ PlatformIO/VSCode<br>
<img src="PlatformIO_testPico.png" width=640> 

### PlatformIO.projects/picoLCD: Simple SoftSPI LCD(ST7789) for RPI-Pico Arduino w/ PlatformIO/VSCode<br>
#### Also works for Arduino-Mbed HardSPI1 w/ ST7735 on PyBASE, see "PyBase7735.cpp" in the folder! <br>
<img src="PicoLCDbuild0528.png" width=640> <img src="https://github.com/jmysu/RPi-Pico/blob/main/pic/PicoLCD7789_0528.gif" width=320>

### PlatformIO.projects/picoPIOLED: Simple PIO LED Blink for RPI-Pico Arduino w/ PlatformIO/VSCode<br>
Toggling the LED w/ PIO...<br>
### PlatformIO.projects/picoPIOLED: Simple PIO LED Blink for RPI-Pico Arduino w/ PlatformIO/VSCode<br>
Driving the LED w/ PIO-PWM...<br>
<img src="picoPWM.gif" width=400> <img src="PyBasePWM.gif" width=400>
### PlatformIO.projects/picoNeoPixel: PIO Neopixels for RPI-Pico Arduino w/ PlatformIO/VSCode<br>
Adapted from Adafruit Neopixels Pico PIO<br>
<img src="picoNeo8.gif" width=400> <br>

### PlatformIO.projects/picoPIOLCD: PIO LCD logo rotating for RPI-Pico Arduino w/ PlatformIO/VSCode<br>
Ported from Pico-SDK, works for PicoKitB(ST7789)(left) & PyBase(ST7735)(right).<br>
Use 2 statemachine PIOs for LCD writing;<br>
Hardware-Interpolation for affine transformation...<br>
<img src="PIcoPIO.png" width=400> <img src="interp3b.png" width=300><br>
<img src="picoPIOLCD.gif" width=300> <img src="FKC16.bmp" width=128> <img src="picoPIO7735.gif" width=400>
<br>

### PlatformIO.projects/picoPIONeopixelOLEDI2C: PIO Neopixels w/ I2C OLED<br>
Attention: pins_arduino.h need to be modified for the non-default I2C pins w/ PicoMate0.90j

<img src="PicoOLED.gif" width=400> 
<br>
<br>

### Reference
[Online PIOASM](https://wokwi.com/tools/pioasm) (GitHub source: https://github.com/wokwi/pioasm-wasm)
