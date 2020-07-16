#ifndef LIGHTCONTROLLERSPY_H
#define LIGHTCONTROLLERSPY_H

#include <string.h>
#include "LightController.h"

int LightControllerSpy_GetLastId(void);
int LightControllerSpy_GetLastState(void);
int LightControllerSpy_GetLightState(int id);
int8_t LightControllerSpy_On(int id);
int8_t LightControllerSpy_Off(int id);


#endif // LIGHTCONTROLLERSPY_H
