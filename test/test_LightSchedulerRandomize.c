#include "unity.h"
#include "LightScheduler.h"
#include "LightController.h"
#include "LightDriverSpy.h"
#include "LightDriver.h"
#include "FakeTimeService.h"
#include "FakeRandomMinute.h"
#include "RandomMinute.h"

int (*savedRandomMinute_Get)(void);

void setUp(void)
{
    LightController_Create();
    LightDriverSpy_AddSpiesToController();
    LightDriverSpy_InstallInterface();
    LightDriverSpy_Reset();
    LightScheduler_Init();
    RandomMinute_setRandomMinuteGetterFuncPtr(FakeRandomMinute_Get);
}

void tearDown(void)
{
    LightController_Destroy();
    LightScheduler_Deinit();
    RandomMinute_ResetAll();
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

void test_LightSchedulerRandomize_TurnsOnEarly(void)
{
    FakeRandomMinute_SetFirstAndIncrement(-10, 5);
    LightScheduler_ScheduleTurnOn(4, EVERYDAY, 600);
    LightScheduler_Randomize(4, EVERYDAY, 600);

    setTimeTo(MONDAY, 600-10);

    LightScheduler_Wakeup();

    checkLightState(4, LIGHT_ON);
}

void test_LightSchedulerRandomize_TurnsOnLater(void)
{
    FakeRandomMinute_SetFirstAndIncrement(20, 5);
    LightScheduler_ScheduleTurnOn(4, EVERYDAY, 600);
    LightScheduler_Randomize(4, EVERYDAY, 600);

    setTimeTo(MONDAY, 600+20);

    LightScheduler_Wakeup();

    checkLightState(4, LIGHT_ON);
}

void test_LightSchedulerRandomize_TurnsOnAfterMidnightWhenSetBeforeMidnight(void)
{
    FakeRandomMinute_SetFirstAndIncrement(10, 5);
    LightScheduler_ScheduleTurnOn(4, EVERYDAY, LIMIT_SCHEDULE_TIME);
    LightScheduler_Randomize(4, EVERYDAY, LIMIT_SCHEDULE_TIME);

    setTimeTo(MONDAY, 10 - 1);

    LightScheduler_Wakeup();

    checkLightState(4, LIGHT_ON);
}
