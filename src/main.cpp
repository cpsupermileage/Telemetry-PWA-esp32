#include "Arduino.h"
#include "speedometer.h"
#include "vesc_link.h"
#include "ble_server.h"

void vescTask(void* parameter);

TaskHandle_t CheckSpeedZero, VescTask, HallEffectTask;

void setup() {
  #ifdef RGB_BUILTIN
  neopixelWrite(RGB_BUILTIN, 0, 0, 0);  // Off
  #endif

  Serial.begin(115200);
  delay(1000); // Wait for serial
  Serial.println("Initializing...");

  #ifdef RGB_BUILTIN
  neopixelWrite(RGB_BUILTIN, RGB_BRIGHTNESS/2, 0, 0);  // Red
  #endif

  // attachInterrupt(digitalPinToInterrupt(2), hallEffectISR, FALLING); //Attaches hall interrupt to pin P2 of Espressif ESP32
  //attachInterrupt(digitalPinToInterrupt(2), hallEffectISR, RISING); //Both seem to work, should test if one is more stable than other on car
  //pinMode(2, INPUT_PULLUP);
  //Serial.println("Interrupts attached...");

  setupBLE();
  Serial.println("Setup BLE...");

  // xTaskCreate(hallEffectTask, "hallEffectTask", 10000, NULL, 1, &HallEffectTask);
  // xTaskCreate(checkSpeedZero, "checkSpeedZero", 10000, NULL, 2, &CheckSpeedZero);
  xTaskCreate(vescTask      , "VescTask"      , 10000, NULL, 2, &VescTask);
  Serial.println("Setup tasks...");

  #ifdef RGB_BUILTIN
  neopixelWrite(RGB_BUILTIN, RGB_BRIGHTNESS/2, RGB_BRIGHTNESS/2, 0);  // Yellow
  #endif

  Serial.println("Done");
}

void loop() 
{
  
}

void vescTask(void* parameter)
{
  // Uart Setup
  UART_setup();
  for(;;)
  {
    // Uart Loop
    THD_SERIAL();
    vTaskDelay(250);
  }
  
}

void hallEffectISR()
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xTaskNotifyFromISR(HallEffectTask, 0, eNoAction, &xHigherPriorityTaskWoken);
    
}
