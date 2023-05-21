#ifndef _RANDOMMINUTE_H
#define _RANDOMMINUTE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

void RandomMinute_Init(int bound);
bool RandomMinute_setRandomMinuteGetterFuncPtr(int (*f)());
int RandomMinute_Get(void);
void RandomMinute_ResetAll(void);

#endif // _RANDOMMINUTE_H
