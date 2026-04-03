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

//#define TACHO_FROM_VESC
#define TACHO_FROM_HALL

// ********************************


#endif