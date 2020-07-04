#ifndef LIGHTSCHEDULER_H
#define LIGHTSCHEDULER_H

#include <stdbool.h>

#define MAX_EVENTS              128
#define LIMIT_SCHEDULE_TIME     1439    // 1439 minutes is 23:59

enum {LS_OK = 0,
      LS_TOO_MANY_EVENTS = -1,
      LS_ID_OUT_OF_BOUNDS = -2,
      LS_INVALID_TIME = -3};

void LightScheduler_Init(void);
void LightScheduler_Deinit(void);
int LightScheduler_ScheduleTurnOn(int id, int day, int minuteOfDay);
int LightScheduler_ScheduleTurnOff(int id, int day, int minuteOfDay);
void LightScheduler_ScheduleRemove(int id, int day, int minuteOfDay);
void LightScheduler_Randomize(int id, int day, int minuteOfDay);
void LightScheduler_Wakeup(void);

#endif // LIGHTSCHEDULER_H
