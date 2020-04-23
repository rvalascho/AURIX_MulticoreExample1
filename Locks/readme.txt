/**
 * \file readme.txt
 * \
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


// This set of files provides an example implementation for different spinlock types
// on the AURIX microcontrollers: 

// mcslock: a FIFO based lock with a single linked queue 

// mskspinlock: masked spinlock

// optimispinlock: first an atomic swap is performed. If the spinlock was not available,
// a simple read is performed to avoid unnecessary blocking of the target memory, 
// and once the spinlock becomes availble, again an atomic swap is performed. 

// prioritylock: priority of tasks is considered during lock aquisition.

// TAS: conventional test-and-set spinlock 

// Ticketlock: a FIFO ordered lock using two global counters 

// TTAS: test-and-test-and-set spinlock


// The different spinlocks can be used with the same API, namely with the functions:
// boolean TryToGetLock(void); 
// void GetLock(void); 
// void ReleaseLock(void); 

// For an example how to use the spinlocks and as starting point for investigating this package 
// please see the file lock_example.c. 

// Furthermore an implementation for synchronizing the cores is provided, see the function 
// void synchronizeOtherCores(void).
// The files were tested with HighTec gcc V4.6.5.0, within the Infineon Software Framework v3.1.
// The files can be imported for example into the folder 0_Src\0_AppSw\TriCore\Locks\.
// The files can be used on any AURIX device, with or without operating system.
// However, for multi-core synchronization, communication (incl. spinlocks) and data exchange 
// it is strongly recommended to use means of a professional operating system, and not 
// proprietary implementations. The files within this package serve only for becoming 
// familiar with multi-core programming or making simple experiments. 


