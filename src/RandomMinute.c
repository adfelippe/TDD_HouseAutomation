#include <time.h>
#include "RandomMinute.h"

int boundTime;

static int RandomMinute_Get_Implementation(void);
int (*RandomMinute_Get)(void) = RandomMinute_Get_Implementation;

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
