#include "wifi_server.h"

#define WIFI_SSID "Cal Poly SMV Electric Car"
#define WIFI_PASSWORD "supermilage"

// We set a Static IP address
IPAddress local_ip(192, 168, 4, 8);
// We set a Gateway IP address
IPAddress gateway(192, 168, 4, 8);
IPAddress subnet(255, 255, 255, 0);


WebServer wifi_server(80);

void sendData() {
    struct data_packet data = get_packet();
    
    // Create JSON Data Packet
    JsonDocument doc;
    doc["tempMOSFET"] = std::to_string(data.tempMOSFET);
    doc["tempMotor"] = std::to_string(data.tempMotor);
    doc["motorCurrent"] = std::to_string(data.motorCurrent);
    doc["inputCurrent"] = std::to_string(data.inputCurrent);
    doc["dutyCycle"] = std::to_string(data.dutyCycle);
    doc["tacho"] = std::to_string(data.tacho);
    doc["rpm"] = std::to_string(data.rpm);
    doc["volts"] = std::to_string(data.volts);
    doc["wattHours"] = std::to_string(data.wattHours);
    doc["error"] = std::to_string(data.error);

    String res;
    serializeJson(doc, res);

    wifi_server.send(200, "application/json", res);
}

void setupWIFI(){
    WiFi.softAPConfig(local_ip, gateway, subnet);
    WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());
    Serial.print("Connect to http://");
    Serial.print(WiFi.softAPIP());
    Serial.println("/");

    wifi_server.on("/", sendData);
    
    wifi_server.begin();
}

void loopWIFI() {
    wifi_server.handleClient();
    delay(2);
}
