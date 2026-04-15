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

    g_sensors.begin();
}

void loop(void) { 
    Serial.println("\n\nRequesting temperatures...");
    g_sensors.requestTemperatures();
    Serial.println("DONE");
  
    for (size_t i = 0; i < NUM_SENSORS; i++) {
        Serial.print("Sensor ");
        Serial.print(i);
        Serial.print(": ");
        
        float temp_c = g_sensors.getTempCByIndex(i);
        if (temp_c == DEVICE_DISCONNECTED_C) {
            Serial.print("Error: Could not read temperature data for sensor ");
            Serial.println(i + 1);
            Serial.println(" (index ");
            Serial.print(i);
            Serial.println("). Skipping the rest.");
            break;
        } else {
            Serial.print(temp_c);
            Serial.print(" °C - ");
            Serial.print(g_sensors.getTempFByIndex(i));
            Serial.println(" °F");
        }
    }

    delay(1000);
}