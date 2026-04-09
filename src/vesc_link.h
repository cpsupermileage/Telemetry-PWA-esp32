#ifndef VESC_LINK_H_
#define VESC_LINK_H_

#include "VescUart.h"
#include <HardwareSerial.h>
#include "struct.h"
#include "config.h"
#ifdef TACHO_FROM_HALL
#include "speedometer.h"
#endif
#ifdef COMM_METHOD_BLE
#include "ble_server.h"
#endif

struct data_packet* get_packet();

void THD_SERIAL(); //main thread function to execute Serial communication
void UART_setup(); //sets up Serial communication with VESC using the VESC_UART library

// void hall_sensor_hit(); //hall sensor processing function, to be run on interrupt
// int hall_time_last = 0; //keep track of time (milliseconds) since last tacho hit


#endif