/**
 * \file atomic_instructions.h
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

#ifndef ATOMIC_INSTRUCTIONS_H_
#define ATOMIC_INSTRUCTIONS_H_





#include "Platform_Types.h"

/* Compile read-write barrier */
#define barrier() asm volatile("": : :"memory")

#ifndef IFX_INLINE
#define IFX_INLINE         static inline          /* makes the function always inlined */
#endif

#define LOCK_INLINE IFX_INLINE

/* atomic compare and swap */
IFX_INLINE boolean cmp_swap(unsigned int* address,
		unsigned int expected_value, unsigned int new_value)
{
    volatile unsigned int instruction_value;
    instruction_value = __cmpswapw(address, new_value, expected_value);
	return (instruction_value) == expected_value;
}

/* atomic clear if equal */
IFX_INLINE boolean cmp_clear(unsigned int* address,
		unsigned int expected_value)
{
	return cmp_swap(address, expected_value, 0);
}


/* atomic swap */
IFX_INLINE unsigned int swap(unsigned int* address,
		unsigned int new_value)
{
	unsigned int old_value;
	old_value = __swap(address, new_value);
	return old_value;
}

/* atomic swap mask */
IFX_INLINE unsigned int swap_msk(unsigned int* address, unsigned int mask,
		unsigned int new_value)
{
	unsigned int swap_lock_value;
	swap_lock_value = __swapmskw(address, new_value, mask);
	return swap_lock_value;
}

/* software fetch and increment implementation */
IFX_INLINE unsigned int swap_incr(unsigned int* address)
{
	unsigned int actual_value = *address;
	unsigned int expected_value;
	do {
		expected_value = actual_value;

		expected_value = __cmpswapw(address, (actual_value+1), actual_value );

		actual_value = expected_value;
	} while (expected_value != actual_value);
	return expected_value;
}

#endif /* ATOMIC_INSTRUCTIONS_H_ */
