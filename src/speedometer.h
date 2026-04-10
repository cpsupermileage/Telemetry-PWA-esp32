#ifndef speedometer_h
#define speedometer_h

#define MIN_TRIGGER_TIME                50000 //Min time in us for a magnet pass to count as a real pass.

void hallEffectTask(void* parameter);
void setInterruptCount(long newCount);
long getInterruptCount();
void hallEffectISR();
long getTacho();

#endif