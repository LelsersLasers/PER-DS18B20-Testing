#include <Arduino.h>

// Required Arduino Libraries
#include <OneWire.h>
#include <DallasTemperature.h>


// If defined, print out all found addresses on the OW bus
// #define SEARCH_MODE_ACTIVE
// If defined, read and print out the temperature data for all found sensors on the OW bus
#define READ_MODE_ACTIVE

#if defined(SEARCH_MODE_ACTIVE) && defined(READ_MODE_ACTIVE)
    #error "Both SEARCH_MODE_ACTIVE and READ_MODE_ACTIVE are defined. Please define only one of them."
#endif


#define LOOP_DELAY (500)
#define ONE_WIRE_PIN (2)
#define NUM_SENSORS (8)
#define LED_PIN (13)


OneWire g_one_wire(ONE_WIRE_PIN);
DallasTemperature g_sensors(&g_one_wire);

size_t loop_counter = 0;


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


void read_temps(void) {
    Serial.print(loop_counter);
    Serial.println(" - Requesting temperatures...");
    g_sensors.requestTemperatures();
    Serial.println("DONE");
  
    for (size_t i = 0; i < NUM_SENSORS; i++) {    
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
            Serial.print(i);
            Serial.print(": ");
            Serial.print(temp_c);
            Serial.print(" °C - ");
            Serial.print(g_sensors.getTempFByIndex(i));
            Serial.println(" °F");
        }
    }
}

void search_addresses(void) {
    uint8_t address[8];
    uint8_t count = 0;



    if (g_one_wire.search(address)) {
        Serial.print("\nuint8_t pin");
        Serial.print(ONE_WIRE_PIN, DEC);
        Serial.println("[][8] = {");
        do {
            count++;
            Serial.println("  {");
            for (uint8_t i = 0; i < 8; i++) {
                Serial.print("0x");
                if (address[i] < 0x10) {
                    Serial.print("0");
                }
                Serial.print(address[i], HEX);
                if (i < 7) { 
                    Serial.print(", ");
                }
            }
            Serial.println("  },");
        } while (g_one_wire.search(address));

        Serial.println("};");
        Serial.print("Total number of sensors found: ");
        Serial.println(count);
    } else {
        Serial.println("No devices found.");
    }
}

void loop(void) {
    loop_counter++;

    Serial.println("\n\n");
 
    #ifdef READ_MODE_ACTIVE
        read_temps();
    #endif
    #ifdef SEARCH_MODE_ACTIVE
        search_addresses();
    #endif

    bool current_led_state = digitalRead(LED_PIN);
    digitalWrite(LED_PIN, !current_led_state);

    delay(LOOP_DELAY);
}