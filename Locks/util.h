/**
 * \file util.h
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




#ifndef UTIL_H
#define UTIL_H

#include "IfxPort.h"
#include "IfxCpu.h"

void myBlink(void);
void blink(int coreId);

void myLedSet(int ledNum, IfxPort_State state);
void ledSet(int coreId, int ledNum, IfxPort_State state);

#define ONE_MILLI 50000
void milliWait(unsigned int ms);
int getCoreId(void);

void synchronizeWithCore(int otherCore);
void synchronizeOtherCores(void);


#define OLDA_ADDRESS								((void*)0x8FE71000)
#define STORE(address, value)						__st32(address, (value))


#endif
