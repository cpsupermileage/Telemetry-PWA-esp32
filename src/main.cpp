#include "Arduino.h"
#include "speedometer.h"
#include "vesc_link.h"

void vescTask(void* parameter);
void wifiTask(void* parameter);

TaskHandle_t CheckSpeedZero, VescTask, HallEffectTask;

void setup() {

  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(2), hallEffectISR, FALLING); //Attaches hall interrupt to pin P2 of Espressif ESP32
  //attachInterrupt(digitalPinToInterrupt(2), hallEffectISR, RISING); //Both seem to work, should test if one is more stable than other on car
  //pinMode(2, INPUT_PULLUP);

  

  xTaskCreate(hallEffectTask, "hallEffectTask", 10000, NULL, 1, &HallEffectTask);
  xTaskCreate(checkSpeedZero, "checkSpeedZero", 10000, NULL, 2, &CheckSpeedZero);
  xTaskCreate(vescTask      , "VescTask"      , 10000, NULL, 2, &VescTask);
  xTaskCreate(wifiTask      , "WifiTask"      , 10000, NULL, 2, &WifiTask);
}

void loop() 
{
  //printRPM();
  //printTacho();
  //printSpeed();
  //delay(1500);
}

// void wifiTask(void* parameter)
// {
//   // Wifi Setup
//     wifi_begin();
//   for(;;)
//   {
//     // Wifi Loop
//     postJSON();
//     delay(250);
//   }
// }

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
