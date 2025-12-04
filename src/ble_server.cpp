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
    charTempMOSFET = service->createCharacteristic(TEMP_MOSFET, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    pCharacteristic1 = pService->createCharacteristic("2A1C", BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    pCharacteristic2 = pService->createCharacteristic("2AEE", BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    pCharacteristic3 = pService->createCharacteristic("2AE0", BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    pCharacteristic4 = pService->createCharacteristic("2C10", BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    pCharacteristic5 = pService->createCharacteristic("2C09", BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    pCharacteristic6 = pService->createCharacteristic("2A67", BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    pCharacteristic7 = pService->createCharacteristic("2B18", BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    pCharacteristic8 = pService->createCharacteristic("2AF2", BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    pCharacteristic9 = pService->createCharacteristic("2BBB", BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

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
        charTempMOSFET->setValue((uint8_t *)&data.tempMOSFET, 4);
        charRPM->setValue((uint8_t *)&data.rpm, 4);
        charRPM->notify();
    }
}