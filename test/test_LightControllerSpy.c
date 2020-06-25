#include "unity.h"
#include "LightControllerSpy.h"

void setUp(void)
{
    LightController_Init();
}

void tearDown(void)
{
    LightController_Deinit();
}

void test_LightControllerSpy_Initialize(void)
{
    TEST_ASSERT_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
    for (int id = 0; id < MAX_LIGHTS; id++) {
        TEST_ASSERT_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLightState(id));
    }
}

void test_LightControllerSpy_RememberTheLastLightIdControlled(void)
{
    LightController_On(10);
    TEST_ASSERT_EQUAL(10, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());
}

void test_LightControllerSpy_RememberAllLightStates(void)
{
    LightController_On(0);
    LightController_Off(31);
    TEST_ASSERT_EQUAL(LIGHT_ON, LightControllerSpy_GetLightState(0));
    TEST_ASSERT_EQUAL(LIGHT_OFF, LightControllerSpy_GetLightState(31));
}
