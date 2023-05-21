#include "unity.h"
#include "LightScheduler.h"
#include "LightController.h"
#include "LightDriverSpy.h"
#include "LightDriver.h"
#include "FakeTimeService.h"
#include "RandomMinute.h"

void setUp(void)
{
    LightController_Create();
    LightDriverSpy_AddSpiesToController();
    LightDriverSpy_InstallInterface();
    LightDriverSpy_Reset();
    LightScheduler_Init();
}

void tearDown(void)
{
    LightController_Destroy();
    LightScheduler_Deinit();
}

void setTimeTo(int day, int minuteOfDay)
{
    FakeTimeService_SetDay(day);
    FakeTimeService_SetMinute(minuteOfDay);
}

void checkLightState(int id, int state)
{
    if (id == LIGHT_ID_UNKNOWN) {
        TEST_ASSERT_EQUAL(id, LightDriverSpy_GetLastId());
        TEST_ASSERT_EQUAL(state, LightDriverSpy_GetLastState());
    } else {
        TEST_ASSERT_EQUAL(state, LightDriverSpy_GetState(id));
    }
}

void test_LightScheduler_NoChangeToLightsDuringInitialization(void)
{
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

void test_LightScheduler_InitStartsOneMinuteAlarm(void)
{
    TEST_ASSERT_EQUAL((void*)LightScheduler_Wakeup, (void*)FakeTimeService_GetAlarmCallback());
    TEST_ASSERT_EQUAL(60, FakeTimeService_GetAlarmPeriod());
}

void test_LightScheduler_DeinitCancelsOneMinuteAlarm(void)
{
    LightScheduler_Deinit();
    TEST_ASSERT_NULL((void*)FakeTimeService_GetAlarmCallback());
    TEST_ASSERT_EQUAL(0, FakeTimeService_GetAlarmPeriod());
}

void test_LightScheduler_ScheduleOnEverydayNotTimeYet(void)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1199);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

void test_LightScheduler_ScheduleOnEverydayItsTime(void)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}

void test_LightScheduler_ScheduleOffEverydayItsTime(void)
{
    LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_OFF);
}

void test_LightScheduler_ScheduleTuesdayItsMonday(void)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

void test_LightScheduler_ScheduleTuesdayItsTuesday(void)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(TUESDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}

void test_LightScheduler_ScheduleWeekendItsFriday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(FRIDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

void test_LightScheduler_ScheduleWeekendItsSaturday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SATURDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}

void test_LightScheduler_ScheduleWeekendItsSunday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SUNDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}

void test_LightScheduler_ScheduleWeekendItsMonday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

void test_LightScheduler_ScheduleWeekdayItsMonday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}

void test_LightScheduler_ScheduleWeekdayItsSunday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    setTimeTo(SUNDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

void test_LightScheduler_RememberTwoEventsAtTheSameTime(void)
{
    LightScheduler_ScheduleTurnOn(3, SUNDAY, 1200);
    LightScheduler_ScheduleTurnOn(12, SUNDAY, 1200);
    setTimeTo(SUNDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
    checkLightState(12, LIGHT_ON);
}

void test_LightScheduler_RejectsTooManyEvents(void)
{
    for (int i = 0; i < MAX_EVENTS; i++)
        TEST_ASSERT_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(6, MONDAY, 600 + i));

    TEST_ASSERT_EQUAL(LS_TOO_MANY_EVENTS, LightScheduler_ScheduleTurnOn(6, MONDAY, 1200));
}

void test_LightScheduler_RemoveFreesScheduleSlot(void)
{
    for (int i = 0; i < MAX_EVENTS; i++)
        TEST_ASSERT_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(6, MONDAY, 600 + i));

    LightScheduler_ScheduleRemove(6, MONDAY, 600);
    TEST_ASSERT_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(11, MONDAY, 1200));
}

void test_LightScheduler_RemoveMultipleScheduleEvent(void)
{
    LightScheduler_ScheduleTurnOn(6, MONDAY, 600);
    LightScheduler_ScheduleTurnOn(7, MONDAY, 600);

    LightScheduler_ScheduleRemove(6, MONDAY, 600);

    setTimeTo(MONDAY, 600);

    LightScheduler_Wakeup();

    checkLightState(6, LIGHT_STATE_UNKNOWN);
    checkLightState(7, LIGHT_ON);
}

void test_LightScheduler_AcceptsValidLightIds(void)
{
    TEST_ASSERT_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(0, MONDAY, 600));
    TEST_ASSERT_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(15, MONDAY, 600));
    TEST_ASSERT_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(31, MONDAY, 600));
}

void test_LightScheduler_RejectsInvalidLightIds(void)
{
    TEST_ASSERT_EQUAL(LS_ID_OUT_OF_BOUNDS, LightScheduler_ScheduleTurnOn(-1, MONDAY, 600));
    TEST_ASSERT_EQUAL(LS_ID_OUT_OF_BOUNDS, LightScheduler_ScheduleTurnOn(32, MONDAY, 600));
}

void test_LightScheduler_RejectsInvalidTimeAfterMidnight(void)
{
    TEST_ASSERT_EQUAL(LS_INVALID_TIME, LightScheduler_ScheduleTurnOn(3, MONDAY, 1500));
}
