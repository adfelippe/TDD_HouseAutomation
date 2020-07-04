#include "LightScheduler.h"
#include "LightController.h"
#include "TimeService.h"
#include "RandomMinute.h"

typedef struct
{
    int id;
    int day;
    int minuteOfDay;
    int event;
} ScheduledLightEvent;

int (*RandomMinute_Get)(void);

static ScheduledLightEvent scheduledEvents[MAX_EVENTS];

static int scheduleEvent(int id, int day, int minuteOfDay, int event);
static void processEventDueNow(Time *time, ScheduledLightEvent *lightEvent);
static void operateLight(ScheduledLightEvent *lightEvent);
static bool DoesLightRespondToday(Time *time, int reactionDay);
static bool isEventScheduled(int i, int id, int day, int minuteOfDay);
static bool isIdOutOfBounds(int id);


void LightScheduler_Init(void)
{
    for (int i = 0; i < MAX_EVENTS; i++)
        scheduledEvents[i].id = UNUSED;

    TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
}

void LightScheduler_Deinit(void)
{
    TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
}

int LightScheduler_ScheduleTurnOn(int id, int day, int minuteOfDay)
{
    return scheduleEvent(id, day, minuteOfDay, TURN_ON);
}

int LightScheduler_ScheduleTurnOff(int id, int day, int minuteOfDay)
{
    return scheduleEvent(id, day, minuteOfDay, TURN_OFF);
}

void LightScheduler_Randomize(int id, int day, int minuteOfDay)
{
    int randomMinute = RandomMinute_Get();

    for (int i = 0; i < MAX_EVENTS; i++) {
        if (isEventScheduled(i, id, day, minuteOfDay))
                scheduledEvents[i].minuteOfDay += randomMinute;
    }
}

void LightScheduler_ScheduleRemove(int id, int day, int minuteOfDay)
{
    for (int i = 0; i < MAX_EVENTS; i++) {
        if (isEventScheduled(i, id, day, minuteOfDay))
                scheduledEvents[i].id = UNUSED;
    }
}

void LightScheduler_Wakeup(void)
{
    Time time;
    TimeService_GetTime(&time);

    for (int i = 0; i < MAX_EVENTS; i++)
        processEventDueNow(&time, &scheduledEvents[i]);
}

static int scheduleEvent(int id, int day, int minuteOfDay, int event)
{
    if (isIdOutOfBounds(id))
        return LS_ID_OUT_OF_BOUNDS;

    for (int i = 0; i < MAX_EVENTS; i++) {
        if (scheduledEvents[i].id == UNUSED) {
            scheduledEvents[i].day = day;
            scheduledEvents[i].minuteOfDay = minuteOfDay;
            scheduledEvents[i].event = event;
            scheduledEvents[i].id = id;
            return LS_OK;
        }
    }

    return LS_TOO_MANY_EVENTS;
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

static bool isEventScheduled(int i, int id, int day, int minuteOfDay)
{
    return (scheduledEvents[i].id == id &&
            scheduledEvents[i].day == day &&
            scheduledEvents[i].minuteOfDay == minuteOfDay);
}

static bool isIdOutOfBounds(int id)
{
    return (id < 0 || id >= MAX_LIGHTS);
}
