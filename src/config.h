#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

// ********************************
// What method to use when communicating with the client
// Uncomment the one to use

#define COMM_METHOD_BLE
//#define COMM_METHOD_WIFI

// ********************************



// ********************************
// What tacho value should be used
// Uncomment the one to use

// #define TACHO_FROM_VESC

#define TACHO_FROM_HALL
#define HALL_PIN D4 // If using tacho from hall sensor, must specify pin

// ********************************



// ********************************
// Vesc communication

// For prototype:
#ifdef CAR_PROTOTYPE
#define VESC_BAUD_RATE 9600
#define VESC_INVERT_TX_RX
#endif
// For urban concept
#ifdef CAR_URBAN_CONCEPT
#define VESC_BAUD_RATE 9600 // To utilize the optocuplers
#endif
// ********************************



#endif