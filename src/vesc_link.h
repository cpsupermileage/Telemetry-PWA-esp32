#ifndef VESC_LINK_H_
#define VESC_LINK_H_

#include "VescUart.h"

#define HALL_PIN 14 //set to the pin we attatch the hall sensor to
#define WHEEL_DIAMETER 20
#define RPM_TO_MPH ((WHEEL_DIAMETER * PI) / 1056) //define the conversion to MPH for later use

// SMV
//define the data struct globally, make it accessible to everything
struct data_packet{ 
    float tempMOSFET;
    float tempMotor;
    float motorCurrent;
    float inputCurrent;
    float dutyCycle;
    float tacho;
    float rpm;
    float volts;
    float wattHours;
    int errors;
};

struct data_packet get_packet();

void THD_SERIAL(); //main thread function to execute serial communication
void UART_setup(); //sets up serial communication with VESC using the VESC_UART library

// void hall_sensor_hit(); //hall sensor processing function, to be run on interrupt
// int hall_time_last = 0; //keep track of time (milliseconds) since last tacho hit


#endif