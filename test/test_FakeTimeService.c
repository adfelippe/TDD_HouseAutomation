#include "unity.h"
#include "FakeTimeService.h"

void setUp(void)
{
    TimeService_Create();
}

void tearDown(void)
{
}

void test_FakeTimeService_Create(void)
{
    TEST_ASSERT_EQUAL(MINUTE_UNKNOWN, TimeService_GetMinute());
    TEST_ASSERT_EQUAL(DAY_UNKNOWN, TimeService_GetDay());
}

void test_FakeTimeService_GetTime(void)
{
    Time time;
    FakeTimeService_SetMinute(55);
    FakeTimeService_SetDay(FRIDAY);
    TimeService_GetTime(&time);
    TEST_ASSERT_EQUAL(55, time.minuteOfDay);
    TEST_ASSERT_EQUAL(FRIDAY, time.dayOfWeek);
}

void test_FakeTimeService_GetMinute(void)
{
    FakeTimeService_SetMinute(21);
    TEST_ASSERT_EQUAL(21, TimeService_GetMinute());
}

void test_FakeTimeService_GetDay(void)
{
    FakeTimeService_SetDay(SATURDAY);
    TEST_ASSERT_EQUAL(SATURDAY, TimeService_GetDay());
}

void test_FakeTimeService_SetMinute(void)
{
    FakeTimeService_SetMinute(42);
    TEST_ASSERT_EQUAL(42, TimeService_GetMinute());
}

void test_FakeTimeService_SetDay(void)
{
    FakeTimeService_SetDay(TUESDAY);
    TEST_ASSERT_EQUAL(TUESDAY, TimeService_GetDay());
}
