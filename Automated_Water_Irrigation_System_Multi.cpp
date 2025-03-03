#include <Arduino.h>
#include <avr/io.h>

// This code is for running 4 pumps at the same timee.

const int DryMoistThresholds[4] = {425, 425, 425, 425};     // Array of moisture thresholds for comparison with CurrMoistLvl.
int CurrMoistLvl;                                           // Current moisture level to compare with DryMoistThreshold.
const int PumpRelayPins[4] = {2, 3, 4, 5};                  // Array of Relay pins connected to the relay module. 
const int MoistSensorPins[4] = {A0, A1, A2, A3};            // Array of Sensor pins connected to the Arduino board. 


void setup() {
  
  Serial.begin(9600);

  
  for (int i = 0; i < 4; i++) {

    // sets the pin for PumpRelayPins to OUTPUT
    pinMode(PumpRelayPins[i], OUTPUT);

    // Sets the current pump relay pins off
    digitalWrite(PumpRelayPins[i], HIGH);

    // sets the pin for MoistSensorPins to INPUT
    pinMode(MoistSensorPins[i], INPUT);
  }

  delay(500);

}

void loop() {

  for (int i = 0; i < 4; i++) {

    // Get the current moisture level from the moisture sensor
    CurrMoistLvl = analogRead(MoistSensorPins[i]);

    // Print out the current moisture level
    Serial.print("Moisture lvl of pin ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(CurrMoistLvl);

    // Compare CurrMoistLvl to the the DryMoistThreshold (the larger the number, the drier the soil)
    // If moisture level is dryer (higher) than the threshold, turn pump on, else off.
    if (CurrMoistLvl > DryMoistThresholds[i]) 
    {
        digitalWrite(PumpRelayPins[i], LOW);
        Serial.println("Pumping.");
    }
    else {
        digitalWrite(PumpRelayPins[i], HIGH);
        Serial.println("Not Pumping.");
    }
  }

  delay(500);
}