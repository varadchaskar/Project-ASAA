// hardware.h
#ifndef HARDWARE_H
#define HARDWARE_H

#include <stdint.h>

// Actuator status structure
typedef struct {
    bool uvLightStatus;
    bool airPumpStatus;
    bool fanStatus;
    bool waterMotorStatus;
} ActuatorStatus_t;

// Function prototypes
void InitializeHardware(void); // Initializes hardware components
void ControlUVLight(uint8_t currentSecond, ActuatorStatus_t* status); // Controls UV light
void ControlAirPump(uint8_t currentSecond, ActuatorStatus_t* status); // Controls air pump
void ControlFan(ActuatorStatus_t* status); // Controls fan based on temperature
void ControlWaterMotor(ActuatorStatus_t* status); // Controls water motor

#endif // HARDWARE_H
