#include "ble_server.h"

int connectedClients = 0;
BLEServer *server;
BLEService *service;

BLECharacteristic *charTempMOSFET;
BLECharacteristic *charTempMotor;
BLECharacteristic *charMotorCurrent;
BLECharacteristic *charInputCurrent;
BLECharacteristic *charDutyCycle;
BLECharacteristic *charTacho;
BLECharacteristic *charRPM;
BLECharacteristic *charVolts;
BLECharacteristic *charWattHours;
BLECharacteristic *charError;

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer *server){
        connectedClients++;
        Serial.print("Client connected. Total clients: ");
        Serial.println(connectedClients);

        //continue advertising for more connections
        BLEDevice::startAdvertising();
    }

    void onDisconnect(BLEServer *server){
        connectedClients--;
        Serial.println("Device disconnected. Total clients: ");
        Serial.println(connectedClients);
    }
};

void setupBLE(){
    // Create the BLE device
    BLEDevice::init("Cal Poly SMV Electric Car");

    // Create the BLEServer
    server = BLEDevice::createServer();
    server->setCallbacks(new MyServerCallbacks());

    // Create BLE services here (add and remove as needed)
    service = server->createService(SERVICE_UUID);


    // Create Characteristics here (unsure of what characteristics exist within services yet)
    charTempMOSFET   = service->createCharacteristic(TEMP_MOSFET, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    charTempMotor    = service->createCharacteristic(TEMP_MOTOR, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    charMotorCurrent = service->createCharacteristic(MOTOR_CURRENT, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    charInputCurrent = service->createCharacteristic(INPUT_CURRENT, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    charDutyCycle    = service->createCharacteristic(DUTY_CYCLE, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    charTacho        = service->createCharacteristic(TACHO, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    charRPM          = service->createCharacteristic(RPM, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    charVolts        = service->createCharacteristic(VOLTS, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    charWattHours    = service->createCharacteristic(WATT_HOURS, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    charError       = service->createCharacteristic(ERROR, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

    service->start();

    // Start advertising
    BLEAdvertising *advertising = BLEDevice::getAdvertising();
    advertising->addServiceUUID(SERVICE_UUID); // espService UUID
    BLEDevice::startAdvertising();
    Serial.println("Waiting for client connections to notify...");
}

void sendBLE(data_packet data){
    // loop sending values with notification to clients
    if (connectedClients > 0) {
        charTempMOSFET->setValue((uint8_t *)&data.tempMOSFET, sizeof(&data.tempMOSFET));
        charTempMotor->setValue((uint8_t *)&data.tempMotor, sizeof(&data.tempMotor));
        charMotorCurrent->setValue((uint8_t *)&data.motorCurrent, sizeof(&data.motorCurrent));
        charInputCurrent->setValue((uint8_t *)&data.inputCurrent, sizeof(&data.inputCurrent));
        charDutyCycle->setValue((uint8_t *)&data.dutyCycle, sizeof(&data.dutyCycle));
        charTacho->setValue((uint8_t *)&data.tacho, sizeof(&data.tacho));
        charRPM->setValue((uint8_t *)&data.rpm, sizeof(&data.rpm));
        charVolts->setValue((uint8_t *)&data.volts, sizeof(&data.volts));
        charWattHours->setValue((uint8_t *)&data.wattHours, sizeof(&data.wattHours));
        charError->setValue((uint8_t *)&data.error, sizeof(&data.error));

        charTempMOSFET->notify();
        charTempMotor->notify();
        charMotorCurrent->notify();
        charInputCurrent->notify();
        charDutyCycle->notify();
        charTacho->notify();
        charRPM->notify();
        charVolts->notify();
        charWattHours->notify();
        charError->notify();
    }
}