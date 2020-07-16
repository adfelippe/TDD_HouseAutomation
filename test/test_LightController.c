#include "unity.h"
#include "LightDriverSpy.h"
#include "LightDriverSpy.h"
#include "LightDriver.h"
#include "LightController.h"


void setUp(void)
{
    LightController_Create();
    LightDriverSpy_AddSpiesToController();
    LightDriverSpy_InstallInterface();
    LightDriverSpy_Reset();
}

void tearDown(void)
{
    LightController_Destroy();
}

void test_LightController_InitializesSuccessfully(void)
{
    TEST_ASSERT_EQUAL(LIGHT_ID_UNKNOWN, LightDriverSpy_GetLastId());
    TEST_ASSERT_EQUAL(LIGHT_STATE_UNKNOWN, LightDriverSpy_GetLastState());
    for (int id = 0; id < MAX_LIGHTS; id++) {
        TEST_ASSERT_EQUAL(LIGHT_STATE_UNKNOWN, LightDriverSpy_GetState(id));
    }
}

void test_LightController_TurnsOnSuccessfully(void)
{
    LightController_On(15);
    TEST_ASSERT_EQUAL(LIGHT_ON, LightDriverSpy_GetState(15));
}

void test_LightController_TurnsOffSuccessfully(void)
{
    LightController_On(7);
    LightController_Off(7);
    TEST_ASSERT_EQUAL(LIGHT_OFF, LightDriverSpy_GetState(7));
}

void test_LightController_WrongLightIdReturnsDifferentState(void)
{
    LightController_On(7);
    TEST_ASSERT_NOT_EQUAL(LIGHT_ON, LightDriverSpy_GetState(10));
}

void test_LightControllerTurnsOnMultipleLightsSuccessfully(void)
{
    LightController_On(7);
    LightController_On(13);
    TEST_ASSERT_EQUAL(LIGHT_ON, LightDriverSpy_GetState(7));
    TEST_ASSERT_EQUAL(LIGHT_ON, LightDriverSpy_GetState(13));
}

void test_LightControllerTurnsOffMultipleLightsSuccessfully(void)
{
    LightController_On(7);
    LightController_On(13);
    LightController_Off(7);
    LightController_Off(13);
    TEST_ASSERT_EQUAL(LIGHT_OFF, LightDriverSpy_GetState(7));
    TEST_ASSERT_EQUAL(LIGHT_OFF, LightDriverSpy_GetState(13));
}

#if 0
void test_LightController_TurnOnRejectsLightIdOutOfBounds(void)
{
    TEST_ASSERT_EQUAL(LIGHT_ID_UNKNOWN, LightController_On(-1));
    TEST_ASSERT_EQUAL(LIGHT_ID_UNKNOWN, LightController_On(33));
}

void test_LightController_TurnOffRejectsLightIdOutOfBounds(void)
{
    TEST_ASSERT_EQUAL(LIGHT_ID_UNKNOWN, LightController_Off(-1));
    TEST_ASSERT_EQUAL(LIGHT_ID_UNKNOWN, LightController_Off(33));
}

void test_LightController_TurnOnReturnsZeroWhenIdIsValid(void)
{
    TEST_ASSERT_EQUAL(LIGHT_ID_OK, LightController_On(5));
}

void test_LightController_TurnOffReturnsZeroWhenIdIsValid(void)
{
    TEST_ASSERT_EQUAL(LIGHT_ID_OK, LightController_Off(5));
}
#endif
