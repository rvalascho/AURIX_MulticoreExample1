/**
 * \file prioritylock.h
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


#ifndef PRIORITYLOCK_H_
#define PRIORITYLOCK_H_

#include "atomic_instructions.h"
#include "spinlock.h"

LOCK_INLINE boolean TryToGetPriorityLock(unsigned long* spinlock,
		volatile unsigned long* waiters, unsigned int priority)
{
	unsigned long my_mask = (1UL << priority);
	unsigned long higher_priority = my_mask - 1;
	return !(*waiters & higher_priority) && TryToGetSpinLock(spinlock);
}

/**
 * priority: between 0 (highest) and 63 (lowest)
 */
LOCK_INLINE void GetPriorityLock(unsigned long* spinlock,
		volatile unsigned long* waiters, unsigned int priority)
{
	unsigned long my_mask = (1UL << priority);
	unsigned long higher_priority = my_mask - 1;

	if (TryToGetPriorityLock(spinlock, waiters, priority))
		return;

	// add our priority to the waiters
	swap_msk(waiters, my_mask, my_mask);

	while (1) {
		while (*waiters & higher_priority)
		{
			if (!(my_mask & *waiters))
			{
				// re-add our priority to the waiters
				swap_msk(waiters, my_mask, my_mask);
			}
		}

		if (TryToGetSpinLock(spinlock))
		{
			// remove our priority from the waiters
			swap_msk(waiters, my_mask, 0);
			return;
		}
	}
}

LOCK_INLINE void ReleasePriorityLock(unsigned long* spinlock)
{
	ReleaseSpinLock(spinlock);
}

#endif /* PRIORITYLOCK_H_ */
