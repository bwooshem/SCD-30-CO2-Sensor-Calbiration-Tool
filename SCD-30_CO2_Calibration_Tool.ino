// DIY CO2 Sensor SCD-30 Forced Recalibration Code
// CC By-NC 2022 Eric & Brian Woo-Shem
// Part of DIY Frugal Arduino CO2 Sensor
// https://github.com/ericwooshem/DIY-Frugal-Arduino-CO2-Sensor
/*
Info:
Code to quickly recalibrate a SCD-30 sensor using Arduino. If sensor is not returning values around 400-450ppm when outside, use this code to reset it.
Add three buttons which allows tuning the calibration value and running repeatedly for multiple sensors without reprogramming. Useful if calibrating multiple sensors.
Also disables automatic self-calibration because it has caused problems.
Afterward it will take measurements and display them to screen indefinitely so you can check your work. 
Does NOT log data. Does NOT use RTC.

LCD = Liquid Crystal Display (Screen)


Resources Used:
https://learn.adafruit.com/adafruit-scd30
*/
#include <Adafruit_SCD30.h> 
#include <LiquidCrystal.h>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// ^Import Packages^
LiquidCrystal lcd(9, 8, 5, 4, 3, 2); // Set LCD Screen pins
Adafruit_SCD30  scd30; // Define Sensor

const int UP = A1;
const int DOWN = A2;
const int RECAL = A0;

int ppmValue = 420;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void setup() { // Start setup
  Serial.begin(9600);
  
  lcd.begin(16, 2); // Set size of LCD screen
  pinMode(6, OUTPUT); // Set what pin 6 does (output)
  pinMode(7, OUTPUT); // Set what pin 7 does (output)
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(RECAL, INPUT);
  
  digitalWrite(7, HIGH); // Set LCD brightness, you can change it if you want to
  analogWrite(6, 120); // Setting LCD contrast, you can change it if you want to
  
  scd30.begin(); // Start CO2 Sensor

  //Print info
  lcd.setCursor(0,0);
  lcd.print("CO2 Recalibrator");
  lcd.setCursor(0,1);
  lcd.print("Firmware V.2.0");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("(C)Eric Woo-Shem");
  delay(1000);
  //lcd.clear();
  
// Force sensor to grab a few measurements to deal with first value = zero and sensor startup time bug.
/*
  int i = 1;
  while(i<4){
    if (scd30.dataReady()){ // If CO2 data
        if (!scd30.read()) //If probelm reading data
          {
            return; // Don't do the the following ↓↓↓
           }
        lcd.clear();
        lcd.setCursor(0,0); // Set LCD Screen cursor position
        lcd.print("Initializing..."); // Write to LCD Screen 
        lcd.setCursor(0,1); // Set LCD Screen cursor position
        lcd.print("Co2: "+String(scd30.CO2)); // Write the CO2 level to the LCD Screen
    }
    i += 1;
  }
  delay(1000);
*/

} // End setup
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void loop() {
  // Repeatedly read in values once the calibration is complete. So you can check the sensor if you have LCD connected.
  if (scd30.dataReady()){ // If CO2 data
    if (!scd30.read()) //If problem reading data
      {
        return; // Don't do the the following ↓↓↓
       }
    lcd.clear();
    lcd.setCursor(0,0); // Set LCD Screen cursor position
    lcd.print("SetTo: " + String(ppmValue)); // Different first line message to indicate it is running calibration code.
    lcd.setCursor(0,1); // Set LCD Screen cursor position
    lcd.print("CO2: " + String(scd30.CO2)); // Write the CO2 level to the LCD Screen

    //int upVal=analogRead(UP);
    //int downVal=analogRead(DOWN);
    //int recVal=analogRead(RECAL);
    int upVal=digitalRead(UP);
    int downVal=digitalRead(DOWN);
    int recVal=digitalRead(RECAL);

    Serial.println("UP: " + String(upVal));
    Serial.println("DOWN: " + String(downVal));
    Serial.println("RECAL: " + String(recVal));
    
    if (upVal==HIGH){
        ppmValue += 10;
    }
    else if (downVal==HIGH){
        ppmValue -= 10;
    }
    else if (recVal==HIGH){
        
        // Disable automatic self-calibration because it tends to make sensors get off over time
        // Note: if set to true, self-calibration is enabled.
        scd30.selfCalibrationEnabled(false);

        // Force recalibration to approximate current outdoor value
        // ONLY DO THIS WHEN OUTSIDE AND SENSOR IS AWAY FROM PEOPLE, WIND, AND OTHER SOURCES OF ERROR
        // Typical outdoor value is 410-440ppm. 
        // Comment out to only disable self-calibration
        scd30.forceRecalibrationWithReference(ppmValue); //IMPORTANT CHANGE THIS VALUE TO YOUR EXPECTED VALUE
        //Serial.println("Recalibrating disconnected");
        int i = 1;
        while(i<4){
            if (scd30.dataReady()){ // If CO2 data
                if (!scd30.read()) //If probelm reading data
                  {
                    return; // Don't do the the following ↓↓↓
                   }
                lcd.clear();
                lcd.setCursor(0,0); // Set LCD Screen cursor position
                lcd.print("Calibrated!"); // Write to LCD Screen 
                Serial.println("Calibrated!"); 
                lcd.setCursor(0,1); // Set LCD Screen cursor position
                lcd.print("CO2: " + String(scd30.CO2)); // Write the CO2 level to the LCD Screen
                Serial.println("CO2: " + String(scd30.CO2));
            }
            else { // if SCD30 not ready
                Serial.println("SCD30 not ready :(");
                lcd.setCursor(0,0); // Set LCD Screen cursor position
                lcd.print("Calibrated!"); // Write to LCD Screen 
                delay(500);
            }
            Serial.println("i = " + String(i));
            i += 1;
        }
    }
  }
}
