/**
 * \file util.c
 * \brief Main function definition for Cpu core 1 .
 *
 * \copyright Copyright (c) 2015 Infineon Technologies AG. All rights reserved.
 *
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

#include "util.h"

void myBlink(void)
{
	blink(getCoreId());
}

//There was a problem..that's how you end up here
void blink(int coreId)
{
	while (1)
	{
		ledSet(coreId, 0, IfxPort_State_low);
		ledSet(coreId, 1, IfxPort_State_low);
		ledSet(coreId, 2, IfxPort_State_low);

		milliWait(200);

		ledSet(coreId, 0, IfxPort_State_high);
		ledSet(coreId, 1, IfxPort_State_high);
		ledSet(coreId, 2, IfxPort_State_high);

		milliWait(200);
	}
}

void myLedSet(int ledNum, IfxPort_State state)
{
	int coreId = getCoreId();
	ledSet(coreId, ledNum, state);
}

void ledSet(int coreId, int ledNum, IfxPort_State state)
{
	int ledId = coreId * 3 + 6 + ledNum;
	IfxPort_setPinState(&MODULE_P13, ledId, state);
}

void milliWait(unsigned int ms)
{
	volatile unsigned int countdown = 50000 * ms;
	while (countdown-- > 0)
		;
}

int getCoreId(void)
{
	return __mfcr(0xFE1c);
}

#ifndef barrier
#define barrier() asm volatile("": : :"memory")
#endif
typedef struct _synchronizator
{
	volatile unsigned int lowerReady;
	volatile unsigned int greaterReady;
} synchronizator;

#pragma section fardata "lmubss"
synchronizator synchronizator_0 = {.lowerReady = 0, .greaterReady = 0}; // between 1 and 2
synchronizator synchronizator_1 = {.lowerReady = 0, .greaterReady = 0}; // between 0 and 1
synchronizator synchronizator_2 = {.lowerReady = 0, .greaterReady = 0}; // between 0 and 2
#pragma section fardata restore

synchronizator* synchronizator_array[3] = { &synchronizator_0, &synchronizator_1, &synchronizator_2 };

#define WAIT_UNTIL(cond) do{ while(!(cond)){ __nop();} }while(0)

void synchronizeWithCore(int otherCore)
{
	//barrier();  May need to do something with this.
	int myCore = getCoreId();
	int index = (myCore + otherCore) % 3;
	synchronizator* sync = synchronizator_array[index];

	if (myCore < otherCore)
	{
		sync->lowerReady = 1;
		WAIT_UNTIL(sync->greaterReady == 1);

		sync->lowerReady = 0;
		WAIT_UNTIL(sync->greaterReady == 0);

		IfxPort_setPinState(&MODULE_P13, 0, IfxPort_State_low);
		IfxPort_setPinState(&MODULE_P13, 1, IfxPort_State_low);
		IfxPort_setPinState(&MODULE_P13, 2, IfxPort_State_low);
	}
	else if (myCore > otherCore)
	{
		WAIT_UNTIL(sync->lowerReady == 1);
		sync->greaterReady = 1;

		WAIT_UNTIL(sync->lowerReady == 0);
		sync->greaterReady = 0;

		IfxPort_setPinState(&MODULE_P13, 0, IfxPort_State_low);
		IfxPort_setPinState(&MODULE_P13, 1, IfxPort_State_low);
		IfxPort_setPinState(&MODULE_P13, 2, IfxPort_State_low);
	}
	else
	{
		blink(myCore);
	}
	//barrier();
}

void synchronizeOtherCores(void)
{
	int myId = getCoreId();
	int i;
	for (i = 0; i < 3; i++)
	{
		if (i == myId)
		{
			continue;
		}
		synchronizeWithCore(i);
	}
}


