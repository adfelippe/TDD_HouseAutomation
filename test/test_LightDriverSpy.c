//- ------------------------------------------------------------------
//-    Copyright (c) James W. Grenning -- All Rights Reserved
//-    For use by owners of Test-Driven Development for Embedded C,
//-    and attendees of Renaissance Software Consulting, Co. training
//-    classes.
//-
//-    Available at http://pragprog.com/titles/jgade/
//-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3
//-
//-    Authorized users may use this source code in your own
//-    projects, however the source code may not be used to
//-    create training material, courses, books, articles, and
//-    the like. We make no guarantees that this source code is
//-    fit for any purpose.
//-
//-    www.renaissancesoftware.net james@renaissancesoftware.net
//- ------------------------------------------------------------------

#include "unity.h"
#include "LightController.h"
#include "LightDriver.h"
#include "LightDriverSpy.h"


LightDriver lightDriverSpy;


void setUp(void)
{
    LightDriverSpy_Reset();
    lightDriverSpy = LightDriverSpy_Create(1);
}

void tearDown(void)
{
    LightDriverSpy_Destroy(lightDriverSpy);
}

void test_LightDriverSpy_Create(void)
{
    TEST_ASSERT_EQUAL(LIGHT_STATE_UNKNOWN, LightDriverSpy_GetState(1));
}

void test_LightDriverSpy_TurnOn(void)
{
    LightDriverSpy_TurnOn(lightDriverSpy);
    TEST_ASSERT_EQUAL(LIGHT_ON, LightDriverSpy_GetState(1));
}

void test_LightDriverSpy_TurnOff(void)
{
    LightDriverSpy_TurnOff(lightDriverSpy);
    TEST_ASSERT_EQUAL(LIGHT_OFF, LightDriverSpy_GetState(1));
}

void test_LightDriverSpy_RecordsLastIdLastTurnOn(void)
{
    LightDriverSpy_TurnOn(lightDriverSpy);
    TEST_ASSERT_EQUAL(1, LightDriverSpy_GetLastId());
    TEST_ASSERT_EQUAL(LIGHT_ON, LightDriverSpy_GetLastState());
}

void test_LightDriverSpy_RecordsLastIdLastTurnOff(void)
{
    LightDriverSpy_TurnOff(lightDriverSpy);
    TEST_ASSERT_EQUAL(1, LightDriverSpy_GetLastId());
    TEST_ASSERT_EQUAL(LIGHT_OFF, LightDriverSpy_GetLastState());
}
