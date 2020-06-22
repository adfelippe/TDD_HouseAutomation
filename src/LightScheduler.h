#ifndef LIGHTSCHEDULER_H
#define LIGHTSCHEDULER_H

#include <stdbool.h>

enum { LIGHT_ID_UNKNOWN = -1, LIGHT_STATE_UNKNOWN = -1 };
enum { LIGHT_OFF = 0, LIGHT_ON = 1 };
enum { TURN_OFF = 0, TURN_ON = 1 };
enum { UNUSED = 0 };

void LightScheduler_Init(void);
void LightScheduler_Deinit(void);
void LightScheduler_ScheduleTurnOn(int id, int day, int minuteOfDay);
void LightScheduler_ScheduleTurnOff(int id, int day, int minuteOfDay);
void LightScheduler_Wakeup(void);

#endif // LIGHTSCHEDULER_H
