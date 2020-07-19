/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
/*- ------------------------------------------------------------------ -*/
/*-    Copyright (c) James W. Grenning -- All Rights Reserved          -*/
/*-    For use by owners of Test-Driven Development for Embedded C,    -*/
/*-    and attendees of Renaissance Software Consulting, Co. training  -*/
/*-    classes.                                                        -*/
/*-                                                                    -*/
/*-    Available at http://pragprog.com/titles/jgade/                  -*/
/*-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3                -*/
/*-                                                                    -*/
/*-    Authorized users may use this source code in your own           -*/
/*-    projects, however the source code may not be used to            -*/
/*-    create training material, courses, books, articles, and         -*/
/*-    the like. We make no guarantees that this source code is        -*/
/*-    fit for any purpose.                                            -*/
/*-                                                                    -*/
/*-    www.renaissancesoftware.net james@renaissancesoftware.net       -*/
/*- ------------------------------------------------------------------ -*/

#include <stdlib.h>
#include <memory.h>
#include "LightDriverSpy.h"


typedef struct LightDriverSpyStruct * LightDriverSpy;

typedef struct LightDriverSpyStruct
{
    LightDriverStruct base;
} LightDriverSpyStruct;

static LightDriverInterfaceStruct interface =
{
    .TurnOn = LightDriverSpy_TurnOn,
    .TurnOff = LightDriverSpy_TurnOff,
    .Destroy = LightDriverSpy_Destroy
};

static int states[MAX_LIGHTS];
static int lastId;
static int lastState;

void LightDriverSpy_Reset(void)
{
    for (int i = 0; i < MAX_LIGHTS; i++){
        states[i] = LIGHT_STATE_UNKNOWN;
    }

    lastId = LIGHT_ID_UNKNOWN;
    lastState = LIGHT_STATE_UNKNOWN;
}

void LightDriverSpy_InstallInterface(void)
{
    LightDriver_SetInterface(&interface);
}

void LightDriverSpy_AddSpiesToController(void)
{
    int i;
    for (i = 0; i < MAX_LIGHTS; i++)
    {
        LightDriver spy = (LightDriver)LightDriverSpy_Create(i);
        LightController_Add(i, spy);
    }
}

LightDriver LightDriverSpy_Create(int id)
{
    LightDriverSpy self = calloc(1, sizeof(LightDriverSpyStruct));
    self->base.vtable = &interface;
    self->base.type = TestLightDriver;
    self->base.id = id;
    return (LightDriver)self;
}

void LightDriverSpy_Destroy(LightDriver base)
{
    LightDriverSpy self = (LightDriverSpy)base;
    free(self);
}

void LightDriverSpy_TurnOn(LightDriver base)
{
    LightDriverSpy self = (LightDriverSpy)base;
    states[self->base.id] = LIGHT_ON;
    lastId = self->base.id;
    lastState = LIGHT_ON;
}

void LightDriverSpy_TurnOff(LightDriver base)
{
    LightDriverSpy self = (LightDriverSpy)base;
    states[self->base.id] = LIGHT_OFF;
    lastId = self->base.id;
    lastState = LIGHT_OFF;
}

int LightDriverSpy_GetState(int id)
{
    return states[id];
}

int LightDriverSpy_GetLastId(void)
{
    return lastId;
}

int LightDriverSpy_GetLastState(void)
{
    return lastState;
}
