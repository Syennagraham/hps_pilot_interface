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

[Arduino and SD Card Reader Integration](#%20hps_pilot_interface%20The%20purpose%20of%20this%20repository%20is%20to%20provide%20a%20HPS%20pilot%20interface%20where%20the%20screen%20will%20become%20**RED**%20if%20the%20pilot%20is%20too%20close%20to%20the%20surface%20or%20the%20bottom%20and%20will%20become%20**GREEN**%20if%20the%20pilot%20is%20in%20the%20middle%20of%20the%20pool%20based%20on%20pressure/depth.%20This%20code%20will%20also%20read%20two%20RPM%20sensors%20and%20their%20average%20RPM%20out%20to%20the%20screen.%20%20%20Depth%20and%20RPM%20Data%20will%20be%20written%20to%20an%20SD%20card%20file.%20Remember%20to%20change%20.txt%20extension%20to%20.csv%20file%20before%20importing%20to%20google%20sheets/excel.%20%20#%20TO%20DO:%20%201.%20Test%20pressure%20sensors%20and%20calibrate%20them%20%202.%20Add%20correct%20depth%20calculation%20data%20for%20accurate%20pool%20data%20%203.%20Test%20SD%20card%20output%20%204.%20Add%20timer%20relay%20for%20lights%20flashing%20%20%20#%20Pin%20Connections%20If%20your%20desired%20setup%20includes%20the%20MSP-EXP432P401R,%20the%20logic%20level%20converter%20%28LLC%29,%20the%20LCD%20screen%20and%20the%20pressure%20sensor,%20use%20these%20pin%20connections%20below.%20!%5BPerf-board%20connections%5D%28https://github.com/Syennagraham/hps_pilot_interface/blob/main/hps_perfboard.png%29%20%20%20##%20Files%20included%20in%20this%20Repository%20These%20codes%20work%20on%20Arduino%20IDE%20software.%20%20%5Bmsp_test_backlight_words.ino%5D%28https://github.com/Syennagraham/hps_pilot_interface/commit/86cd7066902e8e80faa30a492e6f9e214f2fb6d8%20%22Create%20msp_test_backlight_words.ino%22%29%20Tests%20the%20pin%20connections%20from%20the%20MSP%20to%20the%20LCD%20screen.%20It%20will%20change%20the%20background%20colors%20of%20the%20LCD%20screen%20and%20display%20words.%20%20%20%5Bmsp_pressure_sensor.ino%5D%28https://github.com/Syennagraham/hps_pilot_interface/blob/main/msp_pressure_sensor.ino%29%20Reads%20the%20pressure%20sensor%20data%20and%20display%20the%20pressure%20sensor%20data%20on%20the%20LCD%20screen.%20%20%5Barduino_pressure_sensor.ino%5D%28https://github.com/Syennagraham/hps_pilot_interface/blob/main/arduino_pressure_sensor.ino%29%20Reads%20pressure%20sensor%20data%20out%20to%20screen%20using%20Arduino.%20%20%5Barduino_lcd_backlight_control.ino%5D%28https://github.com/Syennagraham/hps_pilot_interface/blob/main/arduino_lcd_backlight_control.ino%29%20Changes%20the%20backlight%20color%20of%20the%20LCD%20screen%20using%20Arduino.%20%20%5BMSP_reset_LCD.ino%5D%28https://github.com/Syennagraham/hps_pilot_interface/blob/main/MSP_reset_LCD.ino%29%20Useful%20for%20resetting%20the%20LCD%20screen.%20%20##%20Helpful%20References%20%5BLCD%20Commands%5D%28https://media.digikey.com/pdf/Data%20Sheets/Sparkfun%20PDFs/AVR_Based_Serial_Enabled_LCDs_HookupGuide_Web.pdf%29%20%20%5BLCD%20-%20Microcontroller%20Hook%20Up%20Guide/Picture%5D%28https://cdn.sparkfun.com/assets/learn_tutorials/7/8/9/logiclevelhighlight2.jpg%29%20%20%5BMSP%20Pin%20Descriptions%5D%28https://energia.nu/pinmaps/img/MSP-EXP432P401R.jpg%29%20%20%5BEmbedded%20Systems%20Design%20with%20the%20Texas%20Instruments%20MSP432%2032-bit%20Processor%5D%28https://www.google.com/books/edition/Embedded_Systems_Design_with_the_Texas_I/EVxtDQAAQBAJ?hl=en&gbpv=0%29%20%20%5BArduino%20and%20SD%20Card%20Reader%20Integration%5D%20%28https://astronomersanonymous.wordpress.com/2016/04/16/arduino-tutorial-for-undergraduate-students/%29)
