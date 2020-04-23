/**
 * \file mskspinlock.h
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


#ifndef MSKSPINLOCK_H_
#define MSKSPINLOCK_H_

#include "atomic_instructions.h"

LOCK_INLINE boolean TryToGetMskSpinLock(unsigned long* address, unsigned long mask)
{
	unsigned long lock_value = *address;
	unsigned long lock_occupancy = (lock_value & mask);
	if (lock_occupancy == 0)
	{
		return cmp_swap(address, lock_value, lock_value | mask);
	}
	return FALSE;
}

LOCK_INLINE void GetMskSpinLock(unsigned long* address, unsigned long mask)
{
	while (!TryToGetMskSpinLock(address, mask))
		;
}

LOCK_INLINE void ReleaseMskSpinLock(unsigned long* address, unsigned long mask)
{
	swap_msk(address, mask, 0);
}

#endif /* MSKSPINLOCK_H_ */
