#ifndef BLE_SERVER_H
#define BLE_SERVER_H

#include <NimBLEDevice.h>
#include <NimBLEUtils.h>
#include <NimBLEServer.h>
#include <Arduino.h>
#include "struct.h"

// UUID for the ESP32
#define SERVICE_UUID "8e1dfb38-f3a5-4b3f-8f99-a30c0f61fc4e"

// Characteristic UUIDS
#define TEMP_MOSFET "2A1E" // Intermediate Temp
#define TEMP_MOTOR "2A1C" // Temp Measurement
#define MOTOR_CURRENT "2AEE" // Electric Current
#define INPUT_CURRENT "2AE0" // Avg Current
#define DUTY_CYCLE "2C10" // Work Cycle Data
#define TACHO "2C09" // Rotational Speed
#define VOLTS "2B18" // Voltage
#define WATT_HOURS "2AF2" // Energy
#define ERROR "2BBB" // Status flags

#define DESC_USER_DESCRIPTION "2901"

#define TEMP_MOSFET_DESC "MOSFET Temperature"
#define TEMP_MOTOR_DESC "Motor Temperature"
#define MOTOR_CURRENT_DESC "Motor Current"
#define INPUT_CURRENT_DESC "Input Current"
#define DUTY_CYCLE_DESC "Duty Cycle"
#define TACHO_DESC "Tacho"
#define VOLTS_DESC "Volts"
#define WATT_HOURS_DESC "Watt Hours"
#define ERROR_DESC "Error Code"


void setupBLE();

void sendBLE(data_packet* data);

#endif