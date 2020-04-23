/**
 * \file lock_example.h
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


#ifndef LOCK_EXAMPLE_H_
#define LOCK_EXAMPLE_H_



#include "atomic_instructions.h"

#define USE_LOCKS 1
#define USE_DSPR  0

#define LOCKS_ON 1

boolean TryToGetLock(void);
// tries to get a spinlock only once

void GetLock(void);
// perform polling until the spinlock becomes available

void ReleaseLock(void);
// release the spinlock

#endif /* LOCK_EXAMPLE_H_ */
