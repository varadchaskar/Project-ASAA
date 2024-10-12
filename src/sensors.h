// sensors.h
#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>

// Function prototypes
void ReadSensors(void);           // Reads all sensors
uint8_t GetTemperature(void);     // Returns temperature
uint8_t GetHumidity(void);        // Returns humidity
uint16_t GetWaterLevel(void);     // Returns water level
bool GetLDRValue(void);           // Returns LDR value
bool GetVibrationValue(void);     // Returns vibration value

#endif // SENSORS_H
