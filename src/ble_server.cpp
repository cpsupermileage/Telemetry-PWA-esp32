#include "BLE_server.h"

int connectedClients = 0;
NimBLEServer *server;
NimBLEService *service;

NimBLECharacteristic *charTempMOSFET;
NimBLECharacteristic *charTempMotor;
NimBLECharacteristic *charMotorCurrent;
NimBLECharacteristic *charInputCurrent;
NimBLECharacteristic *charDutyCycle;
NimBLECharacteristic *charTacho;
NimBLECharacteristic *charRPM;
NimBLECharacteristic *charVolts;
NimBLECharacteristic *charWattHours;
NimBLECharacteristic *charError;

class MyServerCallbacks : public NimBLEServerCallbacks {
    void onConnect(NimBLEServer *server){
        connectedClients++;
        Serial1.print("Client connected. Total clients: ");
        Serial1.println(connectedClients);

        //continue advertising for more connections
        NimBLEDevice::startAdvertising();
    }

    void onDisconnect(NimBLEServer *server){
        connectedClients--;
        Serial1.println("Device disconnected. Total clients: ");
        Serial1.println(connectedClients);
    }
};

void setupBLE(){
    // Create the NimBLE device
    NimBLEDevice::init("Cal Poly SMV Electric Car");

    // Create the NimBLEServer
    server = NimBLEDevice::createServer();
    server->setCallbacks(new MyServerCallbacks());

    // Create NimBLE services here (add and remove as needed)
    service = server->createService(SERVICE_UUID);


    // Create Characteristics here (unsure of what characteristics exist within services yet)
    charTempMOSFET   = service->createCharacteristic(TEMP_MOSFET, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    charTempMotor    = service->createCharacteristic(TEMP_MOTOR, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    charMotorCurrent = service->createCharacteristic(MOTOR_CURRENT, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    charInputCurrent = service->createCharacteristic(INPUT_CURRENT, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    charDutyCycle    = service->createCharacteristic(DUTY_CYCLE, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    charTacho        = service->createCharacteristic(TACHO, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    charRPM          = service->createCharacteristic(RPM, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    charVolts        = service->createCharacteristic(VOLTS, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    charWattHours    = service->createCharacteristic(WATT_HOURS, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    charError       = service->createCharacteristic(ERROR, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

    service->start();

    // Start advertising
    NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->setName("Cal Poly SMV Electric Car");
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->enableScanResponse(true);
    pAdvertising->start();

    Serial1.println("Waiting for client connections to notify...");
}

void sendBLE(data_packet* data){
    // loop sending values with notification to clients
    charTempMOSFET->setValue((uint8_t *)&(data->tempMOSFET), sizeof(data->tempMOSFET));
    charTempMotor->setValue((uint8_t *)&(data->tempMotor), sizeof(data->tempMotor));
    charMotorCurrent->setValue((uint8_t *)&(data->motorCurrent), sizeof(data->motorCurrent));
    charInputCurrent->setValue((uint8_t *)&(data->inputCurrent), sizeof(data->inputCurrent));
    charDutyCycle->setValue((uint8_t *)&(data->dutyCycle), sizeof(data->dutyCycle));
    charTacho->setValue((uint8_t *)&(data->tacho), sizeof(data->tacho));
    charRPM->setValue((uint8_t *)&(data->rpm), sizeof(data->rpm));
    charVolts->setValue((uint8_t *)&(data->volts), sizeof(data->volts));
    charWattHours->setValue((uint8_t *)&(data->wattHours), sizeof(data->wattHours));
    charError->setValue((uint8_t *)&(data->error), sizeof(data->error));
    
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