// sensors.cpp
#include "sensors.h"
#include "constants.h"
#include <Arduino.h>
#include <dht.h>

// External objects
extern dht DHT;

// Static variables
static uint8_t temperature = 0;       // Current temperature
static uint8_t humidity = 0;          // Current humidity
static uint16_t waterLevel = 0;       // Current water level
static bool ldrValue = false;         // LDR sensor value
static bool vibrationValue = false;   // Vibration sensor value

void ReadSensors(void) {
    // Reads DHT sensor
    DHT.read11(DHT_PIN);
    temperature = DHT.temperature;
    humidity = DHT.humidity;

    // Reads water level sensor
    waterLevel = analogRead(WATER_SENSOR_PIN);

    // Reads LDR and vibration sensors
    ldrValue = digitalRead(LDR_PIN);
    vibrationValue = digitalRead(VIBRATION_PIN);
}

// Getter functions
uint8_t GetTemperature(void) {
    return temperature;
}

uint8_t GetHumidity(void) {
    return humidity;
}

uint16_t GetWaterLevel(void) {
    return waterLevel;
}

bool GetLDRValue(void) {
    return ldrValue;
}

bool GetVibrationValue(void) {
    return vibrationValue;
}
