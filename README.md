# SCD-30-CO2-Sensor-Calbiration-Tool
Calibration Tool for the SCD-30 CO₂ sensors with the I2C interface such as those sold by Adafruit. Intended for use when calibrating multiple sensors for the [DIY Frugal Arduino CO2 Sensor](https://github.com/ericwooshem/DIY-Frugal-Arduino-CO2-Sensor/tree/main/Graphics)
![Calibration Tool](https://github.com/bwooshem/SCD-30-CO2-Sensor-Calbiration-Tool/blob/main/CO2_Recalibrator_Tool.png)

## Instructions
Instructions are a work in-progress. 
1. Assemble the [DIY Frugal Arduino CO2 Sensor](https://github.com/ericwooshem/DIY-Frugal-Arduino-CO2-Sensor/tree/main/Graphics)
2. Add 3x push buttons and resistors (anything 1kΩ - 100kΩ is fine) to each of ports A0, A1, and A2. See [the official Arduino instructions for push button circuits](https://docs.arduino.cc/built-in-examples/digital/Button)
3. Load the SCD-30_CO2_Calibrator_Tool.ino code using Arduino IDE.
4. The device defaults to a target setting of 420ppm, a typical outdoor ambient concentration. If you need a different value, press the button connected to A1 to increase the value & button on A2 to decrease it in increments of 10ppm. Note the button re-checks approximately once per second, so you will need to long-press and hold until the value changes.
5. When the target "SetTo:" value is correct, push the button on A0 once to run the calibration. The screen will display "Calibrated!" for a few seconds. It will continue to display CO₂ readings under the "CO2:" heading; leave it running for at least 30 seconds to verify it was set correctly (it may not have set correctly if the CO₂ concentration varied at the moment the button was pressed). 
6. To calibrate additional sensors, simply swap the sensor port to a new sensor. The machine may automatically restart; that is okay.


## Contributors
[Eric Woo-Shem](https://github.com/ericwooshem): Design of original sensor, Arduino & circuit debugging, review & editing.

[Brian Woo-Shem](https://www.brianwooshem.com): Design & programming for calibration tool, documentation, testing and validation.

## License

All text, graphics, and non-code content is licensed [CC BY-NC-SA](https://creativecommons.org/licenses/by-nc-sa/4.0/)    
All code is licensed under the [GNU General Public License v3](https://www.gnu.org/licenses/gpl-3.0.en.html)

RTClib and Adafruit_SCD30 are Copyright (c) Adafruit Industries and used under the open source MIT license.   
Arduino IDE and related components are open source and licensed under the GNU GPL v2 and/or CC BY-SA Arduino.
