#ifndef D_CountingLightDriver_H
#define D_CountingLightDriver_H

#include "LightDriver.h"

LightDriver CountingLightDriver_Create(int id);
int CountingLightDriver_GetCallCount(LightDriver base);

#endif /*_D_CountingLightDriver_H_*/
