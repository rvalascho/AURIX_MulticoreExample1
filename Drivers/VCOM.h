/*
 * VCOM.h
 *
 *  Created on: Feb 8, 2020
 *      Author: valascho
 */

#ifndef DRIVERS_VCOM_H_
#define DRIVERS_VCOM_H_

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "Bsp.h"

#include "Ifx_Console.h"
#include "Ifx_Shell.h"
#include "IfxAsclin_Asc.h"

#define CFG_ASC_BAUDRATE       (115200.0)                   /**< \brief Define the Baudrate */
#define CFG_ASC_RX_BUFFER_SIZE (512)                        /**< \brief Define the Rx buffer size in byte. */
#define CFG_ASC_TX_BUFFER_SIZE (6 * 1024)                   /**< \brief Define the Tx buffer size in byte. */
#define ISR_PRIORITY_VCOM_0_RX      20
#define ISR_PRIORITY_VCOM_0_TX      21
#define ISR_PRIORITY_VCOM_0_EX      22
#define ISR_PROVIDER_ASC_0          0

#define SW_REVISION_DATE    (0x20140630)            // Software date 0xyyyymmdd, with yyyy the year and mm the month and dd the day
#define SW_REVISION         (0x00000103)            // Software version and revision 0x0000vvrr, with vv the version number and rr the revision number

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

typedef struct
{
    uint8 tx[CFG_ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
    uint8 rx[CFG_ASC_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
} AppAscBuffer;

/** \brief Asc information */
typedef struct
{
    AppAscBuffer ascBuffer;                     /**< \brief ASC interface buffer */
    struct
    {
        IfxAsclin_Asc asc0;                     /**< \brief ASC interface */
    }         drivers;

    uint8     txData[5];
    uint8     rxData[5];
    Ifx_SizeT count;
} App_AsclinAsc;

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/

IFX_EXTERN App_AsclinAsc g_AsclinAsc;


void VCOM_Core_Write(char * txbuff);

#endif /* DRIVERS_VCOM_H_ */
