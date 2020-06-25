#include "LightControllerSpy.h"

static int lastId;
static int lastState;
static int lightState[MAX_LIGHTS];

void LightController_Init(void)
{
    lastId = LIGHT_ID_UNKNOWN;
    lastState = LIGHT_STATE_UNKNOWN;
    memset(lightState, LIGHT_STATE_UNKNOWN, sizeof(lightState));
}

void LightController_Deinit(void)
{
}

void LightController_On(int id)
{
    lastId = id;
    lastState = LIGHT_ON;
    lightState[id] = LIGHT_ON;
}

void LightController_Off(int id)
{
    lastId = id;
    lastState = LIGHT_OFF;
    lightState[id] = LIGHT_OFF;
}

int LightControllerSpy_GetLastId(void)
{
    return lastId;
}

int LightControllerSpy_GetLastState(void)
{
    return lastState;
}

int LightControllerSpy_GetLightState(int id)
{
    return lightState[id];
}
