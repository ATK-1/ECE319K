/*
 * Switch.c
 *
 *  Created on: Nov 5, 2023
 *      Author:
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
// LaunchPad.h defines all the indices into the PINCM table

#define PB24INDEX 51 // SPI0_CS3  SPI0_CS1  TIMA0_C3  TIMG12_C1 TIMA0_C1N TIMA1_C0N
#define PB25INDEX 55 // UART0_CTS SPI0_CS0  TIMA_FAL2
#define PB26INDEX 56 // UART0_RTS SPI0_CS1  TIMA0_C3  TIMG6_C0  TIMA1_C0
#define PB27INDEX 57 // COMP2_OUT SPI1_CS1  TIMA0_C3N TIMG6_C1  TIMA1_C1
#define PB28INDEX  2

void Switch_Init(void){
    IOMUX->SECCFG.PINCM[PB24INDEX]= 0x00040081;
    IOMUX->SECCFG.PINCM[PB25INDEX]= 0x00040081;
    IOMUX->SECCFG.PINCM[PB26INDEX]= 0x00040081;
    IOMUX->SECCFG.PINCM[PB27INDEX]= 0x00040081;
  
}
// return current state of switches
uint32_t Switch_In(void){
    return (GPIOB->DIN31_0 & 0x0F000000)>>24;
}
