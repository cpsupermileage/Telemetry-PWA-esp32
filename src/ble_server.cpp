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
NimBLECharacteristic *charVolts;
NimBLECharacteristic *charWattHours;
NimBLECharacteristic *charError;

NimBLEDescriptor *descTempMOSFET;
NimBLEDescriptor *descTempMotor;
NimBLEDescriptor *descMotorCurrent;
NimBLEDescriptor *descInputCurrent;
NimBLEDescriptor *descDutyCycle;
NimBLEDescriptor *descTacho;
NimBLEDescriptor *descVolts;
NimBLEDescriptor *descWattHours;
NimBLEDescriptor *descError;

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


    // Create Characteristics here
    charTempMOSFET   = service->createCharacteristic(TEMP_MOSFET, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    charTempMotor    = service->createCharacteristic(TEMP_MOTOR, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    charMotorCurrent = service->createCharacteristic(MOTOR_CURRENT, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    charInputCurrent = service->createCharacteristic(INPUT_CURRENT, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    charDutyCycle    = service->createCharacteristic(DUTY_CYCLE, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    charTacho        = service->createCharacteristic(TACHO, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    charVolts        = service->createCharacteristic(VOLTS, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    charWattHours    = service->createCharacteristic(WATT_HOURS, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    charError       = service->createCharacteristic(ERROR, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

    // Create descriptors for each characteristic
    descTempMOSFET   = charTempMOSFET->createDescriptor(DESC_USER_DESCRIPTION);
    descTempMotor    = charTempMotor->createDescriptor(DESC_USER_DESCRIPTION);
    descMotorCurrent = charMotorCurrent->createDescriptor(DESC_USER_DESCRIPTION);
    descInputCurrent = charInputCurrent->createDescriptor(DESC_USER_DESCRIPTION);
    descDutyCycle    = charDutyCycle->createDescriptor(DESC_USER_DESCRIPTION);
    descTacho        = charTacho->createDescriptor(DESC_USER_DESCRIPTION);
    descVolts        = charVolts->createDescriptor(DESC_USER_DESCRIPTION);
    descWattHours    = charWattHours->createDescriptor(DESC_USER_DESCRIPTION);
    descError       = charError->createDescriptor(DESC_USER_DESCRIPTION);

    // Add descriptors to characteristics
    charTempMOSFET->addDescriptor(descTempMOSFET);
    charTempMotor->addDescriptor(descTempMotor);
    charMotorCurrent->addDescriptor(descMotorCurrent);
    charInputCurrent->addDescriptor(descInputCurrent);
    charDutyCycle->addDescriptor(descDutyCycle);
    charTacho->addDescriptor(descTacho);
    charVolts->addDescriptor(descVolts);
    charWattHours->addDescriptor(descWattHours);
    charError->addDescriptor(descError);

    // Set descriptor values
    descTempMOSFET->setValue(TEMP_MOSFET_DESC);
    descTempMotor->setValue(TEMP_MOTOR_DESC);
    descMotorCurrent->setValue(MOTOR_CURRENT_DESC);
    descInputCurrent->setValue(INPUT_CURRENT_DESC);
    descDutyCycle->setValue(DUTY_CYCLE_DESC);
    descTacho->setValue(TACHO_DESC);
    descVolts->setValue(VOLTS_DESC);
    descWattHours->setValue(WATT_HOURS_DESC);
    descError->setValue(ERROR_DESC);


    service->start();

    // Start advertising
    NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->setName("Cal Poly SMV Electric Car");
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->enableScanResponse(true);
    pAdvertising->start();

    Serial1.println("Waiting for client connections to notify...");
}

// Data buffers
byte bufTempMOSFET[sizeof(((data_packet*)0)->tempMOSFET)];
byte bufTempMotor[sizeof(((data_packet*)0)->tempMotor)];
byte bufMotorCurrent[sizeof(((data_packet*)0)->motorCurrent)];
byte bufInputCurrent[sizeof(((data_packet*)0)->inputCurrent)];
byte bufDutyCycle[sizeof(((data_packet*)0)->dutyCycle)];
byte bufTacho[sizeof(((data_packet*)0)->tacho)];
byte bufVolts[sizeof(((data_packet*)0)->volts)];
byte bufWattHours[sizeof(((data_packet*)0)->wattHours)];
byte bufError[sizeof(((data_packet*)0)->error)];

void sendBLE(data_packet* data){
    memcpy(bufTempMOSFET, &(data->tempMOSFET), sizeof(data->tempMOSFET));
    memcpy(bufTempMotor, &(data->tempMotor), sizeof(data->tempMotor));
    memcpy(bufMotorCurrent, &(data->motorCurrent), sizeof(data->motorCurrent));
    memcpy(bufInputCurrent, &(data->inputCurrent), sizeof(data->inputCurrent));
    memcpy(bufDutyCycle, &(data->dutyCycle), sizeof(data->dutyCycle));
    memcpy(bufTacho, &(data->tacho), sizeof(data->tacho));
    memcpy(bufVolts, &(data->volts), sizeof(data->volts));
    memcpy(bufWattHours, &(data->wattHours), sizeof(data->wattHours));
    memcpy(bufError, &(data->error), sizeof(data->error));

    // loop sending values with notification to clients
    charTempMOSFET->setValue((uint8_t *)bufTempMOSFET, sizeof(data->tempMOSFET));
    charTempMotor->setValue((uint8_t *)bufTempMotor, sizeof(data->tempMotor));
    charMotorCurrent->setValue((uint8_t *)bufMotorCurrent, sizeof(data->motorCurrent));
    charInputCurrent->setValue((uint8_t *)bufInputCurrent, sizeof(data->inputCurrent));
    charDutyCycle->setValue((uint8_t *)bufDutyCycle, sizeof(data->dutyCycle));
    charTacho->setValue((uint8_t *)bufTacho, sizeof(data->tacho));
    charVolts->setValue((uint8_t *)bufVolts, sizeof(data->volts));
    charWattHours->setValue((uint8_t *)bufWattHours, sizeof(data->wattHours));
    charError->setValue((uint8_t *)bufError, sizeof(data->error));

    charTempMOSFET->notify();
    charTempMotor->notify();
    charMotorCurrent->notify();
    charInputCurrent->notify();
    charDutyCycle->notify();
    charTacho->notify();
    charVolts->notify();
    charWattHours->notify();
    charError->notify();
}