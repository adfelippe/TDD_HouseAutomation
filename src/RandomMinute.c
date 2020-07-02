#include <time.h>
#include "RandomMinute.h"

int boundTime;

void RandomMinute_Init(int bound)
{
    boundTime = bound;
}

int RandomMinute_Get(int seed)
{
    srand(seed);
    return (rand() % (boundTime + 1)) - boundTime;
}
