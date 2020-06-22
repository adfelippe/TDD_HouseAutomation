#include "LightScheduler.h"
#include "LightController.h"
#include "TimeService.h"

typedef struct
{
    int id;
    int day;
    int minuteOfDay;
    int event;
} ScheduledLightEvent;

static ScheduledLightEvent scheduledEvent;

static void scheduleEvent(int id, int day, int minuteOfDay, int event);
static void processEventDueNow(Time *time, ScheduledLightEvent *lightEvent);
static void operateLight(ScheduledLightEvent *lightEvent);
static bool DoesLightRespondToday(Time *time, int reactionDay);


void LightScheduler_Init(void)
{
    scheduledEvent.id = UNUSED;
    TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
}

void LightScheduler_Deinit(void)
{
    TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
}

void LightScheduler_ScheduleTurnOn(int id, int day, int minuteOfDay)
{
    scheduleEvent(id, day, minuteOfDay, TURN_ON);
}

void LightScheduler_ScheduleTurnOff(int id, int day, int minuteOfDay)
{
    scheduleEvent(id, day, minuteOfDay, TURN_OFF);
}

void LightScheduler_Wakeup(void)
{
    Time time;
    TimeService_GetTime(&time);

    processEventDueNow(&time, &scheduledEvent);
}

static void scheduleEvent(int id, int day, int minuteOfDay, int event)
{
    scheduledEvent.id = id;
    scheduledEvent.minuteOfDay = minuteOfDay;
    scheduledEvent.event = event;
    scheduledEvent.day = day;
}

static void processEventDueNow(Time *time, ScheduledLightEvent *lightEvent)
{
    int reactionDay = lightEvent->day;

    if (lightEvent->id == UNUSED)
        return;

    if (!DoesLightRespondToday(time, reactionDay))
        return;

    if (lightEvent->minuteOfDay != time->minuteOfDay)
        return;

    operateLight(lightEvent);
}

static void operateLight(ScheduledLightEvent *lightEvent)
{
    if (lightEvent->event == TURN_ON)
        LightController_On(lightEvent->id);
    else if (lightEvent->event == TURN_OFF)
        LightController_Off(lightEvent->id);
}

static bool DoesLightRespondToday(Time *time, int reactionDay)
{
    int today = time->dayOfWeek;

    if (reactionDay == EVERYDAY)
        return true;
    if (reactionDay == today)
        return true;
    if (reactionDay == WEEKEND && (today == SATURDAY || today == SUNDAY))
        return true;
    if (reactionDay == WEEKDAY && (today >= MONDAY && today <= FRIDAY))
        return true;
    return false;
}
