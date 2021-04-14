# hps_pilot_interface
The purpose of this repository is to provide a HPS pilot interface where the screen will become **RED** if the pilot is too close to the surface or the bottom and will become **GREEN** if the pilot is in the middle of the pool based on pressure/depth. This code will also read two RPM sensors and their average RPM out to the screen.

# TO DO:
 1. Test pressure sensors and calibrate them
 2. Add correct depth calculation data for accurate pool data
 3. Test SD card output
 4. Add timer relay for lights flashing 

# Pin Connections
If your desired setup includes the MSP-EXP432P401R, the logic level converter (LLC), the LCD screen and the pressure sensor, use these pin connections below.
![Perf-board connections](https://github.com/Syennagraham/hps_pilot_interface/blob/main/hps_perfboard.png)


## Files included in this Repository
Note that these files run on the software [Energia](https://energia.nu/). Energia works exactly like Arduino software but can be used for the MSP-EXP432P401R.

[msp_test_backlight_words.ino](https://github.com/Syennagraham/hps_pilot_interface/commit/86cd7066902e8e80faa30a492e6f9e214f2fb6d8 "Create msp_test_backlight_words.ino")
Tests the pin connections from the MSP to the LCD screen. It will change the background colors of the LCD screen and display words. 

[msp_pressure_sensor.ino](https://github.com/Syennagraham/hps_pilot_interface/blob/main/msp_pressure_sensor.ino)
Reads the pressure sensor data and display the pressure sensor data on the LCD screen.

[arduino_pressure_sensor.ino](https://github.com/Syennagraham/hps_pilot_interface/blob/main/arduino_pressure_sensor.ino)
Reads pressure sensor data out to screen using Arduino.

[arduino_lcd_backlight_control.ino](https://github.com/Syennagraham/hps_pilot_interface/blob/main/arduino_lcd_backlight_control.ino)
Changes the backlight color of the LCD screen using Arduino.

[MSP_reset_LCD.ino](https://github.com/Syennagraham/hps_pilot_interface/blob/main/MSP_reset_LCD.ino)
Useful for resetting the LCD screen.

## Helpful References
[LCD Commands](https://media.digikey.com/pdf/Data%20Sheets/Sparkfun%20PDFs/AVR_Based_Serial_Enabled_LCDs_HookupGuide_Web.pdf)

[LCD - Microcontroller Hook Up Guide/Picture](https://cdn.sparkfun.com/assets/learn_tutorials/7/8/9/logiclevelhighlight2.jpg)

[MSP Pin Descriptions](https://energia.nu/pinmaps/img/MSP-EXP432P401R.jpg)

[Embedded Systems Design with the Texas Instruments MSP432 32-bit Processor](https://www.google.com/books/edition/Embedded_Systems_Design_with_the_Texas_I/EVxtDQAAQBAJ?hl=en&gbpv=0)
