// hardware.cpp
#include "hardware.h"
#include "constants.h"
#include <Arduino.h>
#include <dht.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>

// External objects
extern RTC_DS3231 rtc;
extern dht DHT;
extern Adafruit_SSD1306 display;

// Global variables
uint8_t temperature = 0; // Current temperature
uint8_t humidity = 0;    // Current humidity
uint16_t waterLevel = 0; // Current water level

void InitializeHardware(void) {
    // Initialize serial communication
    Serial.begin(9600);
    Serial.println("Setup Started");

    // Initialize pins
    pinMode(LDR_PIN, INPUT);
    pinMode(VIBRATION_PIN, INPUT);
    pinMode(UV_LIGHT_PIN, OUTPUT);
    pinMode(AIR_PUMP_PIN, OUTPUT);
    pinMode(FAN_PIN, OUTPUT);
    pinMode(WATER_MOTOR_PIN, OUTPUT);

    // Set initial states
    digitalWrite(UV_LIGHT_PIN, HIGH);
    digitalWrite(AIR_PUMP_PIN, HIGH);
    digitalWrite(FAN_PIN, HIGH);
    digitalWrite(WATER_MOTOR_PIN, HIGH);

    // Initialize display
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    Serial.println("Display Initialized");

    // Initialize RTC
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        display.setTextSize(2);
        display.setTextColor(WHITE, BLACK);
        display.setCursor(0, 0);
        display.println("RTC not found");
        display.display();
        while (1);
    }

    if (rtc.lostPower()) {
        Serial.println("RTC lost power, setting the time");
        display.setTextSize(2);
        display.setTextColor(WHITE, BLACK);
        display.setCursor(0, 0);
        display.println("Setting RTC time");
        display.display();
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

void ControlUVLight(uint8_t currentSecond, ActuatorStatus_t* status) {
    // Controls UV light based on time
    if (currentSecond == ON_HOUR && !status->uvLightStatus) {
        Serial.println("Turning UV light on");
        digitalWrite(UV_LIGHT_PIN, LOW);
        status->uvLightStatus = true;
    } else if (currentSecond == OFF_HOUR && status->uvLightStatus) {
        Serial.println("Turning UV light off");
        digitalWrite(UV_LIGHT_PIN, HIGH);
        status->uvLightStatus = false;
    }
}

void ControlAirPump(uint8_t currentSecond, ActuatorStatus_t* status) {
    // Controls air pump based on time
    if (currentSecond >= AIR_PUMP_ON_TIME && currentSecond < AIR_PUMP_OFF_TIME && !status->airPumpStatus) {
        Serial.println("Turning air pump on");
        digitalWrite(AIR_PUMP_PIN, LOW);
        status->airPumpStatus = true;
    } else if ((currentSecond < AIR_PUMP_ON_TIME || currentSecond >= AIR_PUMP_OFF_TIME) && status->airPumpStatus) {
        Serial.println("Turning air pump off");
        digitalWrite(AIR_PUMP_PIN, HIGH);
        status->airPumpStatus = false;
    }
}

void ControlFan(ActuatorStatus_t* status) {
    // Controls fan based on temperature
    if (temperature > HIGH_TEMP_THRESHOLD && !status->fanStatus) {
        Serial.println("Temperature high, turning fan on");
        digitalWrite(FAN_PIN, LOW);
        status->fanStatus = true;
    } else if (temperature <= HIGH_TEMP_THRESHOLD && status->fanStatus) {
        Serial.println("Temperature normal, turning fan off");
        digitalWrite(FAN_PIN, HIGH);
        status->fanStatus = false;
    }
}

void ControlWaterMotor(ActuatorStatus_t* status) {
    // Controls water motor based on water level
    if (waterLevel < WATER_LOW && !status->waterMotorStatus) {
        Serial.println("Water level low, turning water motor on");
        digitalWrite(WATER_MOTOR_PIN, LOW);
        status->waterMotorStatus = true;
    } else if (waterLevel > WATER_MAX && status->waterMotorStatus) {
        Serial.println("Water level high, turning water motor off");
        digitalWrite(WATER_MOTOR_PIN, HIGH);
        status->waterMotorStatus = false;
    }
}
