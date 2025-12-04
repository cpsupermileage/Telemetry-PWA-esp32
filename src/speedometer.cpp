#include "Arduino.h"
#include "speedometer.h"

unsigned long time_now= 0;
unsigned long time_prev = 0;
unsigned int tachoInRevs;
double tachoDistance;
double rpm = 0;
float newSpeed = 0;
float carSpeed = 0;
unsigned int filter_count = 0;
unsigned long time_elapsed = 0;

int interruptCount = 0;

unsigned int speedo_get_tacho()
{
    return tachoInRevs;
}

float speedo_get_speed()
{
    return carSpeed;
}

void checkSpeedZero(void *parameter) //Checks if there hasn't been an interrupt in 5 sec
{
    TickType_t lastWakeTime;
    const TickType_t freqeuency = INTERRUPT_CHECK_CNT_INTERVAL/portTICK_PERIOD_MS;

    while(1)
    {
        lastWakeTime = xTaskGetTickCount();
        vTaskDelayUntil(&lastWakeTime, freqeuency);
        if (interruptCount < MIN_INTERRUPT_COUNT)
        {
            rpm = 0;
            carSpeed = 0;
        }
    
        else
        {
            interruptCount = 0;
        }
    }    
    
    
    
}


float secToMicrosec(float sec)
{
    return (sec * 1000000);
}

void printRPM()
{
    Serial.print("Rip'ems: ");
    Serial.println(rpm);
}

int getInterruptCount()
{
    return interruptCount;
}

void setInterruptCount(int newCount)
{
    interruptCount = newCount;
}

void printTacho()
{
    Serial.println("Total Revolutions: ");
    Serial.println(tachoInRevs);
    Serial.println("\nTachoDistance: ");
    Serial.println(tachoDistance);
 
}

void printSpeed()
{
    Serial.print("Tacho Speed: ");
    Serial.println(carSpeed);
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
        if (time_elapsed >= MIN_TRIGGER_TIME){
            tachoInRevs++;
            tachoDistance = (float) tachoInRevs / PULSES_PER_REV * WHEEL_DIAMETER_INCH / 63360 * PI;
            rpm = secToMicrosec(60) / (time_elapsed * PULSES_PER_REV);
            newSpeed = rpm * WHEEL_DIAMETER_INCH/INCHES_IN_MILE * 60 * PI;
            if ((newSpeed - carSpeed) > MAX_SPEED_DELTA && filter_count < MAX_FILTERS)
            {
                filter_count ++;
            }
            else
            {
                carSpeed = newSpeed;
                filter_count = 0;
            }
            time_prev = time_now;
            
        }
        
        xTaskNotifyWait(0, ULONG_MAX, &ulNotificationValue, portMAX_DELAY);
    }
    
} 

// void hallEffectISROLD() //MAKE INTO HALL EFFECT TASK, MAKE IT SCHEDULE A TASK
// {
//     interruptCount++;
//     time_now = micros();
//     time_elapsed = (time_now - time_prev);
//     if (time_elapsed < MIN_TRIGGER_TIME){
//         return;
//     }
//     tachoInRevs++;
//     tachoDistance = (float) tachoInRevs / PULSES_PER_REV * WHEEL_DIAMETER_INCH / 63360 * PI;
//     rpm = secToMicrosec(60) / (time_elapsed * PULSES_PER_REV);
//     carSpeed = rpm * WHEEL_DIAMETER_INCH/INCHES_IN_MILE * 60 * PI;
//     time_prev = time_now;
// }
