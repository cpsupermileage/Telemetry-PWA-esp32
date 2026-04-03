#include "Arduino.h"
#include "speedometer.h"

unsigned long time_now= 0;
unsigned long time_elapsed = 0;
unsigned long time_prev = 0;
long tachoInRevs;

long interruptCount = 0;

long getTacho()
{
    return tachoInRevs;
}

long getInterruptCount()
{
    return interruptCount;
}

void setInterruptCount(long newCount)
{
    interruptCount = newCount;
}

void hallEffectTask(void* parameter)
{
    uint32_t ulNotificationValue;
    BaseType_t xResult;

    for(;;)
    {
        interruptCount++;
        time_now = micros();
        time_elapsed = (time_now - time_prev);
        time_prev = micros();

        if (time_elapsed >= MIN_TRIGGER_TIME){
            tachoInRevs++;
        }
        
        xTaskNotifyWait(0, ULONG_MAX, &ulNotificationValue, portMAX_DELAY);
    }
    
} 
