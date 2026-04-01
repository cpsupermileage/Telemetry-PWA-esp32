#ifndef STRUCT_H
#define STRUCT_H
#include <Arduino.h>

// SMV
//define the data struct globally, make it accessible to everything
struct data_packet{ 
    float tempMOSFET;
    float tempMotor;
    float motorCurrent;
    float inputCurrent;
    float dutyCycle;
    long tacho;
    float rpm;
    float volts;
    float wattHours;
    uint8_t error;
};

#endif