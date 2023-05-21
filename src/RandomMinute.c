#include <time.h>
#include "RandomMinute.h"

int boundTime;

static int RandomMinute_Get_Implementation(void);
static int (*RandomMinute_Get_)(void) = RandomMinute_Get_Implementation;

void RandomMinute_Init(int bound)
{
    boundTime = bound;
}

static int RandomMinute_Get_Implementation(void)
{
    static unsigned int seed = 0;
    ++seed;
    srand(seed + time(NULL));
    return (rand() % (boundTime * 2 + 1)) - boundTime;
}

bool RandomMinute_setRandomMinuteGetterFuncPtr(int (*f)()) 
{
    if (NULL == f) {
        return false;
    }

    RandomMinute_Get_ = f;
    return true;
}

int RandomMinute_Get(void)
{
    return RandomMinute_Get_();
}

void RandomMinute_ResetAll(void)
{
    boundTime = 0;
    RandomMinute_Get_ = RandomMinute_Get_Implementation;
}