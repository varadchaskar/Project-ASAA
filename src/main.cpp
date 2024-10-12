/*
Author: Varad Chaskar
Project: Advanced Self-Sustaining Agriculture Automation
Date: 5 Mar 2023
Version/Modification No: 14
Description: This code automates agricultural processes such as controlling UV lights, water pumps, and fans based on environmental conditions and time; it uses sensors (LDR, vibration, DHT) to monitor conditions and actuates devices like UV lights, fans, and water pumps.
*/

// Include necessary headers
#include <Arduino.h>
#include "hardware.h"
#include "sensors.h"
#include "constants.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>
#include <dht.h>

// Global objects
RTC_DS3231 rtc; // RTC object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // OLED display object
dht DHT; // DHT sensor object

// Global variables
static bool automaticControlEnabled = true; // Automatic control flag
uint8_t temperature = 0; // Current temperature
uint8_t humidity = 0;    // Current humidity
uint16_t waterLevel = 0; // Current water level

// Function prototypes
void HandleSerialInput(ActuatorStatus_t* status);

void setup() {
    InitializeHardware(); // Initialize hardware
}

void loop() {
    static ActuatorStatus_t actuatorStatus = {false, false, false, false};

    HandleSerialInput(&actuatorStatus); // Handle serial input

    if (automaticControlEnabled) {
        // Automatic control is enabled

        // Get current time
        DateTime now = rtc.now();
        uint8_t currentSecond = now.second();
        uint8_t currentMinute = now.minute();
        uint8_t currentHour = now.hour();

        char timeBuffer[16];
        sprintf(timeBuffer, "%02d:%02d:%02d", currentHour, currentMinute, currentSecond);
        Serial.print("Time: ");
        Serial.println(timeBuffer);

        ReadSensors(); // Read sensors

        // Update global sensor variables
        temperature = GetTemperature();
        humidity = GetHumidity();
        waterLevel = GetWaterLevel();

        // Control actuators
        ControlUVLight(currentSecond, &actuatorStatus);
        ControlAirPump(currentSecond, &actuatorStatus);
        ControlFan(&actuatorStatus);
        ControlWaterMotor(&actuatorStatus);

        // Update display every 10 seconds
        if (currentSecond % 10 == 0) {
            display.clearDisplay();
            display.setTextSize(2);
            display.setTextColor(WHITE, BLACK);
            display.setCursor(0, 0);
            display.println(timeBuffer);
            display.print("Temp:");
            display.println(temperature);
            display.print("Humi:");
            display.println(humidity);
            if (waterLevel > WATER_LOW && waterLevel < WATER_MAX) {
                display.println("Water OK");
            } else {
                display.println("Water Low");
            }
            display.display();
        }
    } else {
        // Automatic control is disabled
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(WHITE, BLACK);
        display.setCursor(0, 0);
        display.println("Automatic");
        display.println("Control");
        display.println("Disabled");
        display.display();
    }

    delay(1000); // Wait 1 second
}

void HandleSerialInput(ActuatorStatus_t* status) {
    // Handles serial input for manual control
    if (Serial.available() > 0) {
        char inputChar = Serial.read();
        // Consume any extra characters
        while (Serial.available() > 0) {
            Serial.read();
        }
        Serial.print("Serial Input: ");
        Serial.println(inputChar);

        switch (inputChar) {
            case 'A':
            case 'a':
                automaticControlEnabled = !automaticControlEnabled;
                if (automaticControlEnabled) {
                    Serial.println("Automatic control enabled");
                } else {
                    Serial.println("Automatic control disabled");
                }
                break;

            case 'B':
            case 'b':
                // Toggle UV light
                if (status->uvLightStatus) {
                    Serial.println("Turning UV light off");
                    digitalWrite(UV_LIGHT_PIN, HIGH);
                    status->uvLightStatus = false;
                } else {
                    Serial.println("Turning UV light on");
                    digitalWrite(UV_LIGHT_PIN, LOW);
                    status->uvLightStatus = true;
                }
                break;

            case 'C':
            case 'c':
                // Toggle air pump
                if (status->airPumpStatus) {
                    Serial.println("Turning air pump off");
                    digitalWrite(AIR_PUMP_PIN, HIGH);
                    status->airPumpStatus = false;
                } else {
                    Serial.println("Turning air pump on");
                    digitalWrite(AIR_PUMP_PIN, LOW);
                    status->airPumpStatus = true;
                }
                break;

            case 'D':
            case 'd':
                // Toggle fan
                if (status->fanStatus) {
                    Serial.println("Turning fan off");
                    digitalWrite(FAN_PIN, HIGH);
                    status->fanStatus = false;
                } else {
                    Serial.println("Turning fan on");
                    digitalWrite(FAN_PIN, LOW);
                    status->fanStatus = true;
                }
                break;

            case 'E':
            case 'e':
                // Toggle water motor
                if (status->waterMotorStatus) {
                    Serial.println("Turning water motor off");
                    digitalWrite(WATER_MOTOR_PIN, HIGH);
                    status->waterMotorStatus = false;
                } else {
                    Serial.println("Turning water motor on");
                    digitalWrite(WATER_MOTOR_PIN, LOW);
                    status->waterMotorStatus = true;
                }
                break;

            default:
                Serial.println("Unknown command");
                break;
        }
    }
}
