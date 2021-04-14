# hps_pilot_interface
The purpose of this repository is to provide a HPS pilot interface where the screen will become **RED** if the pilot is too close to the surface or the bottom and will become **GREEN** if the pilot is in the middle of the pool based on pressure/depth. This code will also read two RPM sensors and their average RPM out to the screen. 

Depth and RPM Data will be written to an SD card file. Remember to change .txt extension to .csv file before importing to google sheets/excel.

# TO DO:
 1. Test pressure sensors and calibrate them
 2. Add correct depth calculation data for accurate pool data
 3. Test SD card output
 4. Add timer relay for lights flashing 

# Pin Connections
If your desired setup includes the MSP-EXP432P401R, the logic level converter (LLC), the LCD screen and the pressure sensor, use these pin connections below.
![Perf-board connections](https://github.com/Syennagraham/hps_pilot_interface/blob/main/hps_perfboard.png)


## Files included in this Repository
These codes work on Arduino IDE software.

[arduino_pressure_sensor.ino](https://github.com/Syennagraham/hps_pilot_interface/blob/main/arduino_pressure_sensor.ino)
Reads pressure sensor data out to screen using Arduino.

[arduino_lcd_backlight_control.ino](https://github.com/Syennagraham/hps_pilot_interface/blob/main/arduino_lcd_backlight_control.ino)
Changes the backlight color of the LCD screen using Arduino.

[arduino_SD_test.ino](https://github.com/Syennagraham/hps_pilot_interface/blob/main/test/sensor_tests/arduino_sd_test.ino)
Test the SD card reader, prints output to a file.

[arduino_rpm_test.ino](https://github.com/Syennagraham/hps_pilot_interface/blob/main/test/sensor_tests/arduino_rpm_test.ino)
Test RPM sensors. 

## Helpful References
[LCD Commands](https://media.digikey.com/pdf/Data%20Sheets/Sparkfun%20PDFs/AVR_Based_Serial_Enabled_LCDs_HookupGuide_Web.pdf)

[LCD - Microcontroller Hook Up Guide/Picture](https://cdn.sparkfun.com/assets/learn_tutorials/7/8/9/logiclevelhighlight2.jpg)

[Arduino and SD Card Reader Integration](https://astronomersanonymous.wordpress.com/2016/04/16/arduino-tutorial-for-undergraduate-students/%29)
