#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

BLEServer *server = NULL;
BLECharacteristic *characteristic = NULL;
int connectedClients = 0;

// UUID for the ESP32
#define SERVICE_UUID "8e1dfb38-f3a5-4b3f-8f99-a30c0f61fc4e"

// UUIDS for UART
#define CHARACTERISTIC_TRANSMIT "82480001-9a25-49fc-99be-2c16d1492d35"
#define CHARACTERISTIC_RECEIVE "82480002-9a25-49fc-99be-2c16d1492d35"

// Characteristic UUIDS
#define TEMP_MOSFET 0x2a1e // Intermediate Temp
#define TEMP_MOTOR 0x2a1c // Temp Measurement
#define MOTOR_CURRENT 0x2aee // Electric Current
#define INPUT_CURRENT 0x2ae0 // Avg Current
#define DUTY_CYCLE 0x2c10 // Work Cycle Data
#define TACHO 0x2c09 // Rotational Speed
#define RPM 0x2a67 // Location and speed
#define VOLTS 0x2b18 // Voltage
#define WATT_HOURS 0x2af2 // Energy
#define ERRORS 0x2bbb // Status flags

class MyServerCallbacks : public BLEServerCallbacks{
    void onConnect(BLEServer *server){
        connectedClients++;
        Serial.print("Client connected. Total clients: ");
        Serial.println(connectedClients);

        //continue advertising for more connections
        CLEDevice::startAdvertising();
    }

    void onDisconnect(BLEServer *server){
        connectedClients--;
        Serial.println("Device disconnected. Total clients: ");
        Serial.println(connectedClients);
    }
}

void setup(){
    Serial.begin(115200); // I assume this is Baudrate

    // Create the BLE device
    BLEDevice::init("ESP32");

    // Create the BLEServer
    server = BLEDevice::createServer();
    server->setCallbacks(new MyServerCallbacks(this));

    // Create BLE services here (add and remove as needed)
    BLEService espService = server->createService(SERVICE_UUID);

    BLEService tempMosfet = server->createService(TEMP_MOSFET);
    BLEService tempMotor = server->createService(TEMP_MOTOR);
    BLEService motorCurrent = server->createService(MOTOR_CURRENT);
    BLEService inputCurrent = server->createService(INPUT_CURRENT);
    BLEService dutyCycle = server->createService(DUTY_CYCLE);
    BLEService tacho = server->createService(TACHO);
    BLEService rpm = server->createService(RPM);
    BLEService volts = server->createService(VOLTS);
    BLEService wattHours = server->createService(WATT_HOURS);
    BLEService errors = server->createService(ERRORS);

    // Create Characteristics here (unsure of what characteristics exist within services yet)
    // *NOTE: Need to add types in front of these 2 as I'm unsure what the typing is for a characteristic (BLECharacteristic ??)
    pCharacteristicTransmit = espService->createCharacteristic(
                        CHARACTERISTIC_TRANSMIT,
                        BLECharacteristic::PROPERTY_READ   |
                        BLECharacteristic::PROPERTY_WRITE  | // Do we need transmit or receive to have the write property to write the value to the server, or write the server value to the client?
                        BLECharacteristic::PROPERTY_NOTIFY |
                        BLECharacteristic::PROPERTY_INDICATE
                        );

    pCharacteristicRecive = espService->createCharacteristic(
                        CHARACTERISTIC_RECIVE,
                        BLECharacteristic::PROPERTY_READ   |
                        BLECharacteristic::PROPERTY_WRITE  |
                        BLECharacteristic::PROPERTY_NOTIFY |
                        BLECharacteristic::PROPERTY_INDICATE
                        );

    // Create a BLE Descriptor
    pCharacteristicTransmit->addDescriptor(new BLE2902());
    pCharacteristicRecive->addDescriptor(new BLE2902());

    // Tells both characteristics to use the same callback methods we defined above to listen for changes
    CharacteristicChangeCallbacks *callbacks = new CharacteristicChangeCallbacks(this);
    pCharacteristicTransmit->setCallbacks(callbacks);
    pCharacteristicRecive->setCallbacks(callbacks);

    // Start the services (unsure of whether to start them automatically or based on user input)
    espService->start();
    // Example: RPM
    rpm->start();

    // Start advertising
    BLEAdvertising *advertising = BLEDevice::getAdvertising();
    advertising->addServiceUUID(SERVICE_UUID); // espService UUID
    advertising->addServiceUUID(RPM);
    // Add more service UUIDs as needed...
    advertising->setScanResponse(false); // Could be true if we need an ack response (at least I think this is what it could be)
    BLEDevice::startAdvertising();
    // advertising->setMinPreferred(); // I assume this has something to do with the min advertising interval
    Serial.println("Waiting for client connections to notify...");
}
