#ifndef _RANDOMMINUTE_H
#define _RANDOMMINUTE_H

#include <stdint.h>
#include <stdlib.h>


void RandomMinute_Init(int bound);
extern int (*RandomMinute_Get)(void);

#endif // _RANDOMMINUTE_H
