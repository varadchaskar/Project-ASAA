#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdint.h>

// Pin Definitions
const uint8_t UV_LIGHT_PIN = 5;       // UV light control pin
const uint8_t AIR_PUMP_PIN = 6;       // Air pump control pin
const uint8_t FAN_PIN = 7;            // Fan control pin
const uint8_t WATER_MOTOR_PIN = 8;    // Water motor control pin
const uint8_t LDR_PIN = 3;            // LDR sensor pin
const uint8_t VIBRATION_PIN = 4;      // Vibration sensor pin
const uint8_t DHT_PIN = 2;            // DHT sensor pin
const uint8_t WATER_SENSOR_PIN = A1;  // Water level sensor pin

// Display Settings
const uint8_t SCREEN_WIDTH = 128;     // OLED display width in pixels
const uint8_t SCREEN_HEIGHT = 64;     // OLED display height in pixels

// Time and Threshold Settings
const uint8_t ON_HOUR = 15;           // Time in seconds to turn on UV light
const uint8_t OFF_HOUR = 45;          // Time in seconds to turn off UV light
const uint8_t HIGH_TEMP_THRESHOLD = 27; // Temperature threshold to turn on fan
const uint8_t AIR_PUMP_ON_TIME = 0;   // Start time in seconds for air pump
const uint8_t AIR_PUMP_OFF_TIME = 15; // End time in seconds for air pump
const uint16_t WATER_MAX = 550;       // Maximum water level
const uint16_t WATER_LOW = 400;       // Minimum water level

#endif // CONSTANTS_H
