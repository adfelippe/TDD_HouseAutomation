#include "LightControllerSpy.h"

static int lastId;
static int lastState;
static int lightState[MAX_LIGHTS];

static bool isIdOutOfBounds(int id);


void LightController_Init(void)
{
    lastId = LIGHT_ID_UNKNOWN;
    lastState = LIGHT_STATE_UNKNOWN;
    memset(lightState, LIGHT_STATE_UNKNOWN, sizeof(lightState));
}

void LightController_Deinit(void)
{
}

int8_t LightController_On(int id)
{
    if (isIdOutOfBounds(id))
        return LIGHT_ID_UNKNOWN;

    lastId = id;
    lastState = LIGHT_ON;
    lightState[id] = LIGHT_ON;

    return LIGHT_ID_OK;
}

int8_t LightController_Off(int id)
{
    if (isIdOutOfBounds(id))
        return LIGHT_ID_UNKNOWN;

    lastId = id;
    lastState = LIGHT_OFF;
    lightState[id] = LIGHT_OFF;

    return LIGHT_ID_OK;
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
    if (isIdOutOfBounds(id))
        return LIGHT_ID_UNKNOWN;
        
    return lightState[id];
}

static bool isIdOutOfBounds(int id)
{
    return (id < 0 || id > MAX_LIGHTS);
}
