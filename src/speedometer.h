#ifndef spedometer_h
#define spedometer_h

#define MIN_INTERRUPT_COUNT             1
#define INTERRUPT_CHECK_CNT_INTERVAL    1750 //milliseconds
#define INCHES_IN_MILE                  63360
#define MIN_TRIGGER_TIME                150000 //Min time in us for a magnet pass to count as a real pass.
#define PULSES_PER_REV                  1 //Magnet pulses per revolution of wheel
#define WHEEL_DIAMETER_INCH             19.5 //Total diameter of driving wheel
#define MAX_SPEED_DELTA                 2  // Max MPH change between pulses
#define MAX_FILTERS                     4 // Max filtered values before update

void hallEffectTask(void* parameter);
void setInterruptCount(int newCount);
int getInterruptCount();
void printRPM();
void hallEffectISR();
float secToMicrosec(float sec);
void checkSpeedZero(void *parameter);
void printTacho();
void printSpeed();
unsigned int speedo_get_tacho();
float speedo_get_speed();




#endif