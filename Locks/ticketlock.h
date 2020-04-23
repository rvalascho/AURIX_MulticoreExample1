/**
 * \file ticketlock.h
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


#ifndef TICKETLOCK_H_
#define TICKETLOCK_H_

#include "atomic_instructions.h"

IFX_INLINE void GetTicketLock(unsigned long* next_ticket,
		volatile unsigned long* serving_ticket)
{
	unsigned long my_ticket = swap_incr(next_ticket);
	while (my_ticket != *serving_ticket)
		;
}

IFX_INLINE void ReleaseTicketLock(unsigned long* serving_ticket)
{
	*serving_ticket += 1;
}

IFX_INLINE boolean TryToGetTicketLock(unsigned long* next_ticket,
		volatile unsigned long* serving_ticket)
{
	unsigned long next = *next_ticket;
	if (next == *serving_ticket)
	{
		// no one is waiting
		return cmp_swap(next_ticket, next, next + 1);
	}
	return FALSE;
}

#endif /* TICKETLOCK_H_ */
