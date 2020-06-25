#ifndef LIGHTCONTROLLERSPY_H
#define LIGHTCONTROLLERSPY_H

#include <string.h>
#include "LightController.h"

int LightControllerSpy_GetLastId(void);
int LightControllerSpy_GetLastState(void);
int LightControllerSpy_GetLightState(int id);


#endif // LIGHTCONTROLLERSPY_H
