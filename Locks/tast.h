/**
 * \file tast.h
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

#ifndef TAST_H_
#define TAST_H_

#include "atomic_instructions.h"

#define spinlockFREE 0
#define spinlockBUSY 1

IFX_INLINE boolean TryToGetTAST(volatile unsigned long* address)
{
	return swap(address, spinlockBUSY) == spinlockFREE;
}

IFX_INLINE void GetTAST(volatile unsigned long* address)
{
	while (swap(address, spinlockBUSY) == spinlockBUSY)
	{
		while (*address == spinlockBUSY)
			;
	}
}

IFX_INLINE void ReleaseTAST(unsigned long* address)
{
	*address = spinlockFREE;
}

#endif /* TAST_H_ */
