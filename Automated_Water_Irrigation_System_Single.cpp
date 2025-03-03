#include <Arduino.h>
#include <avr/io.h>

// This codes is runs 1 pump

const int DryMoistThreshold = 425;  // Moisture threshold for comparison with CurrMoistLvl.
int CurrMoistLvl;                   // Current moisture level to compare with DryMoistThreshold.
const int PumpRelayPin = 2;         // Relay pin number connected to the pump. (output)
const int MoistSensorPin = A0;      // Sensor pin number connected to the Arduino board. (input)


void setup() {
  
  Serial.begin(9600);

  // sets the pin for PumpRelayPin to OUTPUT
  pinMode(PumpRelayPin, OUTPUT);

  // Sets the current pump relay pin off
  digitalWrite(PumpRelayPin, LOW);

  // sets the pin for MoistSensorPin to INPUT
  pinMode(MoistSensorPin, INPUT);

  delay(500);

}

void loop() {
  
  // Get the current moisture level from the moisture sensor
  CurrMoistLvl = analogRead(MoistSensorPin);

  // Print out the current moisture level
  Serial.println("Moisture lvl:");
  Serial.println(CurrMoistLvl);
  
  // Compare CurrMoistLvl to the the DryMoistThreshold (the larger the number, the drier the soil)
  // If moisture level is dryer (higher) than the threshold, turn pump on, else off.
  if (CurrMoistLvl > DryMoistThreshold) 
  {
    digitalWrite(PumpRelayPin, LOW);
    Serial.println("Pumping.");
  }
  else {
    digitalWrite(PumpRelayPin, HIGH);
    Serial.println("Not Pumping.");
  }

  delay(500);
}