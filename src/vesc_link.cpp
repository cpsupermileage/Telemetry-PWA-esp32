#include "vesc_link.h"
#include "speedometer.h"
#include <HardwareSerial.h>
#include "ble_server.h"

VescUart UART; //object that will recive all the values from vesc
struct data_packet next_data;

void THD_SERIAL(){
    Serial.println("Getting values...");
    if (UART.getVescValues()){

        #ifdef RGB_BUILTIN
        neopixelWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS/2, 0);  // Green
        #endif

        //if the data call succeeds, populate the struct.
        next_data.tempMOSFET = UART.data.tempMosfet;
        next_data.tempMotor = UART.data.tempMotor;
        next_data.motorCurrent = UART.data.avgMotorCurrent;
        next_data.inputCurrent = UART.data.avgInputCurrent;
        next_data.dutyCycle = UART.data.dutyCycleNow;
        next_data.tacho = UART.data.tachometerAbs;
        next_data.rpm = UART.data.rpm;
        next_data.volts = UART.data.inpVoltage;
        next_data.wattHours = UART.data.wattHours;
        next_data.error = UART.data.error;

        Serial.print("tempMosfet: ");
        Serial.print(next_data.tempMOSFET);
        Serial.print(" tempMotor: ");
        Serial.print(next_data.tempMotor);
        Serial.print(" motorCurrent: ");
        Serial.print(next_data.motorCurrent);
        Serial.print(" inputCurrent: ");
        Serial.print(next_data.inputCurrent);
        Serial.print(" dutyCycle: ");
        Serial.print(next_data.dutyCycle);
        Serial.print(" tacho: ");
        Serial.print(next_data.tacho);
        Serial.print(" rpm: ");
        Serial.print(next_data.rpm);
        Serial.print(" volts: ");
        Serial.print(next_data.volts);
        Serial.print(" wattHours: ");
        Serial.print(next_data.wattHours);
        Serial.print(" error: ");
        Serial.print(next_data.error);
        Serial.println();

        sendBLE(next_data);
    }
}

void UART_setup() {

    Serial1.begin(115200, SERIAL_8N1, TX, RX);
    UART.setSerialPort(&Serial1);

    Serial.println("Serial initialized...");
}

struct data_packet get_packet(){
    return next_data;
}


