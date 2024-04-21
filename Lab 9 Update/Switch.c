/*
 * Switch.c
 *
 *  Created on: Nov 5, 2023
 *      Author:
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
// LaunchPad.h defines all the indices into the PINCM table

#define PA24INDEX 53 // UART2_RX  SPI0_CS2  TIMA0_C3N TIMG0_C1  UART3_RTS TIMG7_C1  TIMA1_C1
#define PA25INDEX 54 // UART3_RX  SPI1_CS3  TIMG12_C1 TIMA0_C3  TIMA0_C1N
#define PA26INDEX 58 // UART3_TX  SPI1_CS0  TIMG8_C0  TIMA_FAL0 CAN_TX    TIMG7_C0
#define PA27INDEX 59 // RTC_OUT   SPI1_CS1  TIMG8_C1  TIMA_FAL2 CAN_RX    TIMG7_C1
#define PA28INDEX  2 // UART0_TX  I2C0_SDA  TIMA0_C3  TIMA_FAL0 TIMG7_C0  TIMA1_C0

void Switch_Init(void){
    IOMUX->SECCFG.PINCM[PA24INDEX]= 0x00040081;
    IOMUX->SECCFG.PINCM[PA25INDEX]= 0x00040081;
    IOMUX->SECCFG.PINCM[PA26INDEX]= 0x00040081;
    IOMUX->SECCFG.PINCM[PA27INDEX]= 0x00040081;
    IOMUX->SECCFG.PINCM[PA28INDEX]= 0x00040081;
  
}
// return current state of switches
uint32_t Switch_In(void){
    return (GPIOB->DIN31_0 & 0x0F000000)>>24;
}
