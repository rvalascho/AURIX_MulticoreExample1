/**
 * \file mcslock.h
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



#ifndef MCSLOCK_H_
#define MCSLOCK_H_

#include "atomic_instructions.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct mcslock_t mcslock_t;
struct mcslock_t
{
	volatile mcslock_t *next;
	volatile int spin;
};
typedef struct mcslock_t *mcslock;

LOCK_INLINE boolean mcs_cmp_swap(mcslock *tail_p, mcslock_t *expected_value,
		mcslock_t *new_value)
{
	return cmp_swap((unsigned long*) tail_p, (unsigned long) expected_value,
			(unsigned long) new_value);
}

LOCK_INLINE mcslock_t* mcs_swap(mcslock *tail_p, mcslock_t *new_value)
{
	return (mcslock_t*) swap((unsigned long*) tail_p, (unsigned long) new_value);
}

LOCK_INLINE void GetMCSLock(mcslock *tail_p, mcslock_t *me)
{
	mcslock_t *tail;

	me->next = NULL;
	me->spin = 0;

	tail = mcs_swap(tail_p, me);
	if (tail == NULL)
		return;

	tail->next = me;
	barrier();
	while (!me->spin)
		;

	return;
}

LOCK_INLINE void ReleaseMCSLock(mcslock *tail_p, mcslock_t *me)
{
	if (!me->next)
	{
		if (mcs_cmp_swap(tail_p, me, NULL))
		{
			return;
		}

		while (!me->next)
			;
	}

	/* Unlock next one */
	me->next->spin = 1;
}

LOCK_INLINE boolean TryToGetMCSLock(mcslock *tail_p, mcslock_t *me)
{
	me->next = NULL;
	me->spin = 0;

	return mcs_cmp_swap(tail_p, NULL, me);
}

#endif /* MCSLOCK_H_ */
