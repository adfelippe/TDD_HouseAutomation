#include "unity.h"
#include "LightDriver.h"

#define NON_SENSE_POINTER   (LightDriver)~0
static LightDriver savedDriver = NON_SENSE_POINTER;
static void shouldNotBeCalled(LightDriver self) { savedDriver = self; }

LightDriverInterfaceStruct interface =
{
    shouldNotBeCalled,
    shouldNotBeCalled,
    shouldNotBeCalled
};

LightDriverStruct testDriver =
{
    "testDriver",
    13
};

void setUp(void)
{
}

void tearDown(void)
{
}

void test_LightDriver_NullDriverDoesNotCrash(void)
{
    LightDriver_SetInterface(&interface);
    LightDriver_TurnOn(NULL);
    LightDriver_TurnOff(NULL);
    LightDriver_Destroy(NULL);
    TEST_ASSERT_EQUAL(NON_SENSE_POINTER, savedDriver);
}

void test_LightDriver_NullInterfaceDoesNotCrash(void)
{
    LightDriver_SetInterface(NULL);
    LightDriver_TurnOn(&testDriver);
    LightDriver_TurnOff(&testDriver);
    LightDriver_Destroy(&testDriver);
    TEST_ASSERT_EQUAL(NON_SENSE_POINTER, savedDriver);
}
