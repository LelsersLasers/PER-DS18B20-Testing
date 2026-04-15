#include <Arduino.h>

// Required Arduino Libraries
#include <OneWire.h>
#include <DallasTemperature.h>


#define ONE_WIRE_PIN (2)
#define NUM_SENSORS (1)


OneWire g_one_wire(ONE_WIRE_PIN);

DallasTemperature g_sensors(&g_one_wire);

void setup(void) {
    Serial.begin(9600);
    Serial.println("Simple Teensy based setup to test our E-meter therm harness.");
    Serial.println("Read a chain of parasitic DS18B20s.");
    Serial.print("OneWire bus on pin: ");
    Serial.println(ONE_WIRE_PIN);
    Serial.print("Number of sensors: ");
    Serial.println(NUM_SENSORS);

void loop() {
  // put your main code here, to run repeatedly:

    g_sensors.begin();
}
