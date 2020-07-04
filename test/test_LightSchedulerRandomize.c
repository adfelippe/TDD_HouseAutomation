#include "unity.h"
#include "LightScheduler.h"
#include "LightControllerSpy.h"
#include "FakeTimeService.h"
#include "FakeRandomMinute.h"
#include "RandomMinute.h"

int (*savedRandomMinute_Get)(void);
int (*RandomMinute_Get)(void);

void setUp(void)
{
    LightController_Init();
    LightScheduler_Init();
    savedRandomMinute_Get = RandomMinute_Get;
    RandomMinute_Get = FakeRandomMinute_Get;
}

void tearDown(void)
{
    LightController_Deinit();
    LightScheduler_Deinit();
    RandomMinute_Get = savedRandomMinute_Get;
}

void setTimeTo(int day, int minuteOfDay)
{
    FakeTimeService_SetDay(day);
    FakeTimeService_SetMinute(minuteOfDay);
}

void checkLightState(int id, int state)
{
    if (id == LIGHT_ID_UNKNOWN) {
        TEST_ASSERT_EQUAL(id, LightControllerSpy_GetLastId());
        TEST_ASSERT_EQUAL(state, LightControllerSpy_GetLastState());
    } else {
        TEST_ASSERT_EQUAL(state, LightControllerSpy_GetLightState(id));
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
