#include <Arduino.h>

// Required Arduino Libraries
#include <OneWire.h>
#include <DallasTemperature.h>


#define LOOP_DELAY (500)
#define ONE_WIRE_PIN (2)
#define LED_PIN (13)


OneWire g_one_wire(ONE_WIRE_PIN);
DallasTemperature g_sensors(&g_one_wire);

size_t loop_counter = 0;


void setup(void) {
    Serial.begin(9600);
    Serial.println("Simple Teensy based setup to test our E-meter therm harness.");
    Serial.println("Read a chain of parasitic DS18B20s.");

    pinMode(LED_PIN, OUTPUT);

    g_sensors.begin();
}


// Returns the number of sensors found
int read_temps(void) {
    Serial.print(loop_counter);
    Serial.println(" - Requesting temperatures...");
    g_sensors.requestTemperatures();
    Serial.println("DONE");

    int found_sensors = g_sensors.getDeviceCount();
    Serial.print("Found ");
    Serial.print(found_sensors);
    Serial.println(" sensors.");
  
    for (int i = 0; i < found_sensors; i++) {    
        float temp_c = g_sensors.getTempCByIndex(i);
        if (temp_c == DEVICE_DISCONNECTED_C) {
            Serial.print("Error: Could not read temperature data for sensor ");
            Serial.print(i + 1);
            Serial.print(" (index ");
            Serial.print(i);
            Serial.println("). Skipping the rest.");
            break;
        } else {
            Serial.print("Sensor ");
            uint8_t address[8] = { 0 };
            g_sensors.getAddress(address, i);
            long long id_decimal = 0;
            for (uint8_t j = 0; j < 8; j++) {
                id_decimal |= (long long)address[j] << j;
            }
            Serial.print(id_decimal);
            Serial.print(": ");
            Serial.print(temp_c);
            Serial.print(" °C - ");
            Serial.print(g_sensors.getTempFByIndex(i));
            Serial.println(" °F");
        }
    }

    return found_sensors;
}


void loop(void) {
    loop_counter++;

    Serial.println("\n");
 
    int found_sensors = read_temps();

    bool current_led_state = digitalRead(LED_PIN);
    digitalWrite(LED_PIN, !current_led_state);

    delay(LOOP_DELAY);
}