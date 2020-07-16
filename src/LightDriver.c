#include <stdio.h>
#include "LightDriver.h"
#include "LightDriverSpy.h"

static LightDriverInterface interface = NULL;

static bool isDriverValid(LightDriver self);


void LightDriver_SetInterface(LightDriverInterface i)
{
    interface = i;
}

void LightDriver_TurnOn(LightDriver driver)
{
    if (isDriverValid(driver))
        interface->TurnOn(driver);
}

void LightDriver_TurnOff(LightDriver driver)
{
    if (isDriverValid(driver))
        interface->TurnOff(driver);
}

void LightDriver_Destroy(LightDriver driver)
{
    if (isDriverValid(driver))
        interface->Destroy(driver);
}

static bool isDriverValid(LightDriver self)
{
    return (interface && self);
}
