#ifndef BLE_SERVER_H
#define BLE_SERVER_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <Arduino.h>
#include "vesc_link.h"

// UUID for the ESP32
#define SERVICE_UUID "8e1dfb38-f3a5-4b3f-8f99-a30c0f61fc4e"

// Characteristic UUIDS
#define TEMP_MOSFET "2A1E" // Intermediate Temp
#define TEMP_MOTOR 0x2a1c // Temp Measurement
#define MOTOR_CURRENT 0x2aee // Electric Current
#define INPUT_CURRENT 0x2ae0 // Avg Current
#define DUTY_CYCLE 0x2c10 // Work Cycle Data
#define TACHO 0x2c09 // Rotational Speed
#define RPM 0x2a67 // Location and speed
#define VOLTS 0x2b18 // Voltage
#define WATT_HOURS 0x2af2 // Energy
#define ERRORS 0x2bbb // Status flags


void setupBLE();

void sendBLE(data_packet data);

#endif