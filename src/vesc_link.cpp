#include "vesc_link.h"
#include "speedometer.h"
#include <HardwareSerial.h>
#include "ble_server.h"

VescUart UART; //object that will recive all the values from vesc
struct data_packet next_data;

void THD_SERIAL(){
        //Serial.println("SerialThread Running...");
        // next_data.speed_wheel = speedo_get_speed();
        // next_data.tacho_wheel = speedo_get_tacho();
        
    //takes in a pointer to an int which will be set to 1 by WIFI thread when it is ready for the next packet.
    //we set it to 0 in this thread when we are done writing to indicate to WIFI new data is ready
    //read the data from the VESC only if we are rdy, if else we continue doing nothing till this gets set
        if (UART.getVescValues()){
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

            sendBLE(next_data);
        }
}

void UART_setup() {

    Serial1.begin(115200, SERIAL_8N1, 16, 17); 
    while (!Serial1) {;} //wait for serial to start
    UART.setSerialPort(&Serial1);
}

struct data_packet get_packet(){
    return next_data;
}


