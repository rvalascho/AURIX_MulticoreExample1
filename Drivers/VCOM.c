#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "Compilers.h"
#include "IfxAsclin_Asc.h"
#include "Assert.h"
#include "VCOM.h"
#include <stdio.h>

/******************************************************************************/
/*-----------------------------Global Variables-------------------------------*/
/******************************************************************************/

App_AsclinAsc g_AsclinAsc;

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/


IFX_INTERRUPT(ISR_VCOM_0_rx, 0, ISR_PRIORITY_VCOM_0_RX);
IFX_INTERRUPT(ISR_VCOM_0_tx, 0, ISR_PRIORITY_VCOM_0_TX);
IFX_INTERRUPT(ISR_VCOM_0_ex, 0, ISR_PRIORITY_VCOM_0_EX);


/** \brief Handle Asc0 Rx interrupt
 *
 * \isrProvider \ref ISR_PROVIDER_ASC_0
 * \isrPriority \ref ISR_PRIORITY_ASC_0_RX
 *
 * - Configuration of this interrupt is done by Asc_If_init()
 * - This interrupt is raised each time a data have been received on the serial interface.
 *   and Asc_If_receiveIrq() will be called
 */
void ISR_VCOM_0_rx(void)
{
    IfxCpu_enableInterrupts();
    IfxAsclin_Asc_isrReceive(&g_AsclinAsc.drivers.asc0);
}


/** \brief Handle Asc0 Tx interrupt
 *
 * \isrProvider \ref ISR_PROVIDER_ASC_0
 * \isrPriority \ref ISR_PRIORITY_ASC_0_TX
 *
 * - Configuration of this interrupt is done by Asc_If_init()
 * - This interrupt is raised each time the serial interface transmit buffer get empty
 *   and Asc_If_transmitIrq() will be called
 */
void ISR_VCOM_0_tx(void)
{
    IfxCpu_enableInterrupts();
    IfxAsclin_Asc_isrTransmit(&g_AsclinAsc.drivers.asc0);
}


/** \brief Handle Asc0 Ex interrupt.
 *
 * \isrProvider \ref ISR_PROVIDER_ASC_0
 * \isrPriority \ref ISR_PRIORITY_ASC_0_EX
 *
 * - Configuration of this interrupt is done by Asc_If_init()
 * - This interrupt is raised each time an error occurs on the serial interface and
 *   Asc_If_errorIrq() will be called.
 */
void ISR_VCOM_0_ex(void)
{
    IfxCpu_enableInterrupts();
    IfxAsclin_Asc_isrError(&g_AsclinAsc.drivers.asc0);
}

void initVCOMSerialInterface(void)
{
    /* disable interrupts */
    boolean              interruptState = IfxCpu_disableInterrupts();

    /* create module config */
    IfxAsclin_Asc_Config ascConfig;
    IfxAsclin_Asc_initModuleConfig(&ascConfig, &MODULE_ASCLIN0);

    /* set the desired baudrate */
    ascConfig.baudrate.prescaler    = 1;
    ascConfig.baudrate.baudrate     = CFG_ASC_BAUDRATE; /* FDR values will be calculated in initModule */
    ascConfig.baudrate.oversampling = IfxAsclin_OversamplingFactor_4;

    /* ISR priorities and interrupt target */
    ascConfig.interrupt.txPriority    = ISR_PRIORITY_VCOM_0_TX;
    ascConfig.interrupt.rxPriority    = ISR_PRIORITY_VCOM_0_RX;
    ascConfig.interrupt.erPriority    = ISR_PRIORITY_VCOM_0_EX;
    ascConfig.interrupt.typeOfService = (IfxSrc_Tos)IfxCpu_getCoreIndex();

    /* FIFO configuration */
    ascConfig.txBuffer     = g_AsclinAsc.ascBuffer.tx;
    ascConfig.txBufferSize = CFG_ASC_TX_BUFFER_SIZE;

    ascConfig.rxBuffer     = g_AsclinAsc.ascBuffer.rx;
    ascConfig.rxBufferSize = CFG_ASC_RX_BUFFER_SIZE;

    /* pin configuration */
    const IfxAsclin_Asc_Pins pins = {
           NULL,                     IfxPort_InputMode_pullUp,        /* CTS pin not used */
           &IfxAsclin0_RXA_P14_1_IN, IfxPort_InputMode_pullUp,        /* Rx pin */
           NULL,                     IfxPort_OutputMode_pushPull,     /* RTS pin not used */
           &IfxAsclin0_TX_P14_0_OUT, IfxPort_OutputMode_pushPull,     /* Tx pin */
           IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    ascConfig.pins = &pins;

    /* initialize module */
    IfxAsclin_Asc_initModule(&g_AsclinAsc.drivers.asc0, &ascConfig);

    /* enable interrupts again */
    IfxCpu_restoreInterrupts(interruptState);
}

void VCOM_Core_Write(char * txbuff)
{
    g_AsclinAsc.count = 1;

    while(txbuff[0]!=NULL)
    {
        IfxAsclin_Asc_write(&g_AsclinAsc.drivers.asc0, txbuff, &g_AsclinAsc.count, TIME_INFINITE);
        txbuff++;
    }
}
