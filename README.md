# PER-DS18B20-Testing

Simple Teensy based setup to test our E-meter therm harness. (Read a chain of parasitic DS18B20s.)

Based on: https://randomnerdtutorials.com/guide-for-ds18b20-temperature-sensor-with-arduino/

## Required Arduino Libraries

- [OneWire](https://github.com/paulStoffregen/oneWire)
- [DallasTemperature](https://github.com/milesburton/Arduino-Temperature-Control-Library)

## 4/21/2026 Status

| Module         | Sensor #1   | Sensor #2                          |
| -------------- | ----------- | ---------------------------------- |
| A              | 30712       | 26622                              |
| B              | Not working | 28604                              |
| C              | Not working | 12284                              |
| D              | 6136        | 26554                              |
| E              | 16380       | 24574                              |
| G              | 20474       | 30714                              |
| H              | Not working | Not working                        |
| I              | 16382       | Not working 99% of the time (4088) |
| J              | 28670       | 1980                               |
| Loose test one | 30714       |                                    |

## Notes about the ID

The id's are recorded as follows:
```c
long long id_decimal = 0;
for (uint8_t i = 0; i < 8; i++) {
	id_decimal |= (long long)address[i] << i;
}
```

I did not look in the datasheet if the byte order is correct or not, but the IDs are all unique
and they were consistently calculated as above, so it doesn't really matter to us.