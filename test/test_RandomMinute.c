
#include <string.h>
#include "unity.h"
#include "RandomMinute.h"

enum {BOUND = 30};

int minute;

void setUp(void)
{
    RandomMinute_Init(BOUND);
}

void tearDown(void)
{
}

void AssetMinuteIsInRange(void)
{
    if (minute < -BOUND || minute > BOUND) {
        printf("Bad minute value: %d\n", minute);
        TEST_FAIL_MESSAGE("Minute out of range");
    }
}

void test_RandomMinute_GetIsInRange(void)
{
    for (int i = 0; i < 100; i++) {
        minute = RandomMinute_Get();
        AssetMinuteIsInRange();
    }
}

void test_RandomMinute_AllPossibleValues(void)
{
    int hit[2 * BOUND + 1];
    memset(hit, 0, sizeof(hit));

    for (int i = 0; i < 512; i++) {
        minute = RandomMinute_Get();
        AssetMinuteIsInRange();
        hit[minute + BOUND]++;
    }

    for (int i = 0; i < 2 * BOUND + 1; i++) {
        TEST_ASSERT_TRUE(hit[i] > 0);
    }
}
