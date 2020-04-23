/**
 * \file lock_example.c
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



// Select your preferred spin lock type with the macro definition below.
// TTAS (test - test - and - set) provides for AURIX a good compromise between performance
// and overhead.

#define USE_SPIN 		0
#define USE_MSKSPIN1 	0
#define USE_MSKSPIN2 	0
#define USE_MCS 		0
#define USE_TICKET 		0
#define USE_PRIORITY 	0

#define USE_TAS 		0
#define USE_TTAS 		1
#define USE_TAST 		0


#include "lock_example.h"


#if USE_MSKSPIN1 + USE_MSKSPIN2 + USE_SPIN + USE_MCS + USE_TICKET + USE_PRIORITY + USE_TAS + USE_TAST + USE_TTAS != 1
#error "Please choose ONE lock algorithm"
#endif




#if USE_SPIN
#include "spinlock.h"

unsigned long spinlock_var = spinlockFREE;
unsigned long* spinlock_p = &spinlock_var;

boolean TryToGetLock(void)
{
	return TryToGetSpinLock(spinlock_p);
}

void GetLock(void)
{
	GetSpinLock(spinlock_p);
}

void ReleaseLock(void)
{
	ReleaseSpinLock(spinlock_p);
}

#endif

#if USE_MSKSPIN1 || USE_MSKSPIN2
#include "mskspinlock.h"

unsigned long spinlock_var = 0;
unsigned long* spinlock_p = &spinlock_var;
#if USE_MSKSPIN1
unsigned long mask = 0b1;
#else
unsigned long mask = 0b110;
#endif

boolean TryToGetLock(void)
{
	return TryToGetMskSpinLock(spinlock_p, mask);
}

void GetLock(void)
{
	GetMskSpinLock(spinlock_p, mask);
}

void ReleaseLock(void)
{
	ReleaseMskSpinLock(spinlock_p, mask);
}

#endif


#if USE_MCS
#include "mcslock.h"
#include "communication.h"

mcslock_t *current_tail = NULL;

#pragma section fardata "data_cpu0"
mcslock_t core_lock_0;
#pragma section fardata restore

#pragma section fardata "data_cpu1"
mcslock_t core_lock_1;
#pragma section fardata restore

#pragma section fardata "data_cpu2"
mcslock_t core_lock_2;
#pragma section fardata restore

mcslock_t* core_lock[3] = { &core_lock_0, &core_lock_1, &core_lock_2 };

mcslock_t* my_lock(void)
{
	int id = getCoreId();
	return core_lock[id];
}

boolean TryToGetLock(void)
{
	return TryToGetMCSLock(&current_tail, my_lock());
}

void GetLock(void)
{
	return GetMCSLock(&current_tail, my_lock());
}

void ReleaseLock(void)
{
	return ReleaseMCSLock(&current_tail, my_lock());
}

#endif


#if USE_TICKET
#include "ticketlock.h"

unsigned long next_ticket = 0;
unsigned long serving_ticket = 0;

boolean TryToGetLock(void)
{
	return TryToGetTicketLock(&next_ticket, &serving_ticket);
}

void GetLock(void)
{
	return GetTicketLock(&next_ticket, &serving_ticket);
}

void ReleaseLock(void)
{
	return ReleaseTicketLock(&serving_ticket);
}

#endif

#if USE_PRIORITY
#include "prioritylock.h"

unsigned long spinlock_var = spinlockFREE;
unsigned long* spinlock_p = &spinlock_var;
unsigned long waiters = 0;

#include "communication.h"

unsigned int my_prio(void)
{
	switch (getCoreId())
	{
		case 0:
		case 2:
			return 0;
		default:
			return 10;
	}
}

boolean TryToGetLock(void)
{
	return TryToGetPriorityLock(spinlock_p, &waiters, my_prio());
}

void GetLock(void)
{
	return GetPriorityLock(spinlock_p, &waiters, my_prio());
}

void ReleaseLock(void)
{
	return ReleasePriorityLock(spinlock_p);
}

#endif


#if USE_TAS
#include "tas.h"

#pragma section fardata "data_cpu0"
unsigned long spinlock_var = spinlockFREE;
unsigned long* spinlock_p = &spinlock_var;
#pragma section fardata restore

boolean TryToGetLock(void)
{
	return TryToGetTAS(spinlock_p);
}

void GetLock(void)
{
	GetTAS(spinlock_p);
}

void ReleaseLock(void)
{
	ReleaseTAS(spinlock_p);
}

#endif

#if USE_TAST
#include "tast.h"

#pragma section fardata "data_cpu0"
unsigned long spinlock_var = spinlockFREE;
unsigned long* spinlock_p = &spinlock_var;
#pragma section fardata restore

boolean TryToGetLock(void)
{
	return TryToGetTAST(spinlock_p);
}

void GetLock(void)
{
	GetTAST(spinlock_p);
}

void ReleaseLock(void)
{
	ReleaseTAST(spinlock_p);
}

#endif

#if USE_TTAS
#include "ttas.h"

#if USE_DSPR
#pragma section fardata "data_cpu0"
unsigned int spinlock_var = spinlockFREE;
unsigned int* spinlock_p = &spinlock_var;
#pragma section fardata restore

#else
#pragma section fardata "lmudata"
unsigned int spinlock_var = spinlockFREE;
unsigned int* spinlock_p = &spinlock_var;
#pragma section fardata restore
#endif

boolean TryToGetLock(void)
{
	return TryToGetTTAS(spinlock_p);
}

void GetLock(void)
{
	GetTTAS(spinlock_p);
}

void ReleaseLock(void)
{
	ReleaseTTAS(spinlock_p);
}

#endif
