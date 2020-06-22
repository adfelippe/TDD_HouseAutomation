#ifndef LIGHTSCHEDULER_H
#define LIGHTSCHEDULER_H

#include <stdbool.h>

void LightScheduler_Init(void);
void LightScheduler_Deinit(void);
void LightScheduler_ScheduleTurnOn(int id, int day, int minuteOfDay);
void LightScheduler_ScheduleTurnOff(int id, int day, int minuteOfDay);
void LightScheduler_Wakeup(void);

#endif // LIGHTSCHEDULER_H
