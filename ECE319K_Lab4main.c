/* ECE319K_Lab4main.c
 * Traffic light FSM
 * ECE319H students must use pointers for next state
 * ECE319K students can use indices or pointers for next state
 * Put your names here or look silly
  */

#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "../inc/Clock.h"
#include "../inc/UART.h"
#include "../inc/Timer.h"
#include "../inc/Dump.h"  // student's Lab 3
#include <stdio.h>
#include <string.h>
// put both EIDs in the next two lines
const char EID1[] = "LDA798"; //  ;replace abc123 with your EID
const char EID2[] = "ATK836"; //  ;replace abc123 with your EID

struct State {
    char state[5];
    uint32_t out;
    uint32_t Time;
    uint32_t Next[8];
};
typedef const struct State State_t;
#define southG      0
#define southYW     1
#define southYP     2
#define westG       3
#define westYP      4
#define westYS      5
#define pedesG      6
#define pedesYW1    7
#define pedesYS1    8
#define pedesOW1    9
#define pedesOS1    10
#define pedesYW2    11
#define pedesYS2    12
#define pedesOW2    13
#define pedesOS2    14
#define allRS       15
#define allRW       16
#define allRP       17
#define southRed    (1<<2)
#define southGreen  (1)
#define southYellow (1<<1)
#define westRed     (1<<8)
#define westGreen   (1<<6)
#define westYellow  (1<<7)
#define pedesRed    (1<<26)
#define pedesWhite  (1<<22)|(1<<27)|(1<<26)
#define allRed (1<<2)|(1<<8)|(1<<26)
uint32_t i=southG;
State_t FSM[18]={
              {"sG",southGreen|pedesRed|westRed,300,{southG,southYW,southG,southYW,southYP,southYP,southYP,southYP}},
              {"sYW",southYellow|pedesRed|westRed,100, {allRW,allRW,allRW,allRW,allRW,allRW,allRW,allRW}},
              {"sYP",southYellow|pedesRed|westRed,100,{allRP,allRP,allRP,allRP,allRP,allRP,allRP,allRP}},
              {"wG",southRed|pedesRed|westGreen,300,{westG,westG,westYS,westYS,westYP,westYP,westYP,westYS}},
              {"wYP",southRed|pedesRed|westYellow,100,{allRP,allRP,allRP,allRP,allRP,allRP,allRP,allRP}},
              {"wYS",southRed|pedesRed|westYellow,100,{allRS,allRS,allRS,allRS,allRS,allRS,allRS,allRS}},
              {"pG",southRed|pedesWhite|westRed,300,{pedesG,pedesYW1,pedesYS1,pedesYS1,pedesG,pedesYW1,pedesYS1,pedesYW1}},
              {"pYW1",southRed|pedesRed|westRed,100,{pedesOW1,pedesOW1,pedesOW1,pedesOW1,pedesOW1,pedesOW1,pedesOW1,pedesOW1}},
              {"pYS1",southRed|pedesRed|westRed,100,{pedesOS1,pedesOS1,pedesOS1,pedesOS1,pedesOS1,pedesOS1,pedesOS1,pedesOS1}},
              {"pOW1",southRed|westRed,100,{pedesYW2,pedesYW2,pedesYW2,pedesYW2,pedesYW2,pedesYW2,pedesYW2,pedesYW2}},
              {"pOS1",southRed|westRed,100,{pedesYS2,pedesYS2,pedesYS2,pedesYS2,pedesYS2,pedesYS2,pedesYS2,pedesYS2}},
              {"pYW2",southRed|pedesRed|westRed,100,{pedesOW2,pedesOW2,pedesOW2,pedesOW2,pedesOW2,pedesOW2,pedesOW2,pedesOW2}},
              {"pYS2",southRed|pedesRed|westRed,100,{pedesOS2,pedesOS2,pedesOS2,pedesOS2,pedesOS2,pedesOS2,pedesOS2,pedesOS2}},
              {"pOW2",southRed|westRed,100,{allRW,allRW,allRW,allRW,allRW,allRW,allRW,allRW}},
              {"pOS2",southRed|westRed,100,{allRS,allRS,allRS,allRS,allRS,allRS,allRS,allRS}},
              {"aRS", allRed ,100,{southG,southG,southG,southG,southG,southG,southG,southG}},
              {"aRW",allRed,100,{westG,westG,westG,westG,westG,westG,westG,westG}},
              {"aRP",allRed,100,{pedesG,pedesG,pedesG,pedesG,pedesG,pedesG,pedesG,pedesG}}
              };
// initialize 6 LED outputs and 3 switch inputs
// assumes LaunchPad_Init resets and powers A and B
void Traffic_Init(void){ // assumes LaunchPad_Init resets and powers A and B
 GPIOB->DOE31_0 = GPIOB->DOE31_0 | (southGreen|southRed|southYellow|westGreen|westRed|westYellow|pedesWhite);// write this
 IOMUX->SECCFG.PINCM[PB17INDEX]  = (uint32_t) 0x00040081;
 IOMUX->SECCFG.PINCM[PB16INDEX]  = (uint32_t) 0x00040081;
 IOMUX->SECCFG.PINCM[PB15INDEX]  = (uint32_t) 0x00040081;
 IOMUX->SECCFG.PINCM[PB0INDEX]  = (uint32_t) 0x00000081;
 IOMUX->SECCFG.PINCM[PB1INDEX]  = (uint32_t) 0x00000081;
 IOMUX->SECCFG.PINCM[PB2INDEX]  = (uint32_t) 0x00000081;
 IOMUX->SECCFG.PINCM[PB6INDEX]  = (uint32_t) 0x00000081;
 IOMUX->SECCFG.PINCM[PB7INDEX]  = (uint32_t) 0x00000081;
 IOMUX->SECCFG.PINCM[PB8INDEX]  = (uint32_t) 0x00000081;
}
/* Activate LEDs
* Inputs: data1,data2,data3
*   specify what these means
* Output: none
* Feel free to change this. But, if you change the way it works, change the test programs too
* Be friendly*/
uint32_t Traffic_Out(uint32_t Input){

 GPIOB->DOUTCLR31_0 =southGreen|southRed|southYellow|westGreen|westRed|westYellow|pedesWhite;
 GPIOB->DOUTSET31_0 = FSM[i].out;
 SysTick_Wait10ms(FSM[i].Time);
 i=FSM[i].Next[Input];
 return ((i<<15)|(GPIOB->DOUT31_0)&(southGreen|southRed|southYellow|westGreen|westRed|westYellow|pedesWhite));

 // write this

}
/* Read sensors
 * Input: none
 * Output: sensor values
*   specify what these means
* Feel free to change this. But, if you change the way it works, change the test programs too
 */
uint32_t Traffic_In(void){
uint32_t in;
in= (GPIOB->DIN31_0) & ((1<<17)|(1<<16)|(1<<15));
in=(in>>15);// write this
 return in; // replace this line
}
// use main1 to determine Lab4 assignment
void Lab4Grader(int mode);
void Grader_Init(void);
int main1(void){ // main1
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Lab4Grader(0); // print assignment, no grading
  while(1){
  }
}
// use main2 to debug LED outputs
int main2(void){ // main2
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Grader_Init();  // execute this line before your code
  Traffic_Init(); // your Lab 4 initialization
  if((GPIOB->DOE31_0 & 0x20)==0){
    UART_OutString("access to GPIOB->DOE31_0 should be friendly.\n\r");
  }
  Debug_Init();   // Lab 3 debugging
  UART_Init();
  UART_OutString("Lab 4, Spring 2024, Step 1. Debug LEDs\n\r");
  UART_OutString("EID1= "); UART_OutString((char*)EID1); UART_OutString("\n\r");
  UART_OutString("EID2= "); UART_OutString((char*)EID2); UART_OutString("\n\r");
  while(1){
    //write debug code to test your Traffic_Out
	// Call Traffic_Out testing all LED patterns
	// Lab 3 dump to record output values
	
    Clock_Delay(40000000); // 0.5s
    if((GPIOB->DOUT31_0&0x20) == 0){
      UART_OutString("DOUT not friendly\n\r");
    }
  }
}
// use main3 to debug the three input switches
int main3(void){ // main3
  uint32_t last=0,now;
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Traffic_Init(); // your Lab 4 initialization
  Debug_Init();   // Lab 3 debugging
  UART_Init();
  __enable_irq(); // UART uses interrupts
  UART_OutString("Lab 4, Spring 2024, Step 2. Debug switches\n\r");
  UART_OutString("EID1= "); UART_OutString((char*)EID1); UART_OutString("\n\r");
  UART_OutString("EID2= "); UART_OutString((char*)EID2); UART_OutString("\n\r");
  while(1){
    now = Traffic_In(); // Your Lab4 input
    if(now != last){ // change
      UART_OutString("Switch= 0x"); UART_OutUHex(now); UART_OutString("\n\r");
      Debug_Dump(now);
    }
    last = now;
    Clock_Delay(800000); // 10ms, to debounce switch
  }
}
// use main4 to debug using your dump
// proving your machine cycles through all states
int main(void){// main4
uint32_t input;
  Clock_Init80MHz(0);
  LaunchPad_Init();
  LaunchPad_LED1off();
  Traffic_Init(); // your Lab 4 initialization
  Debug_Init();   // Lab 3 debugging
  UART_Init();
  __enable_irq(); // UART uses interrupts
  UART_OutString("Lab 4, Spring 2024, Step 3. Debug FSM cycle\n\r");
  UART_OutString("EID1= "); UART_OutString((char*)EID1); UART_OutString("\n\r");
  UART_OutString("EID2= "); UART_OutString((char*)EID2); UART_OutString("\n\r");
 // initialize your FSM
  SysTick_Init();   // Initialize SysTick for software waits

  while(1){
      uint32_t output;
   output = Traffic_Out(7); // 1) output depending on state using Traffic_Out
   uint32_t success;
   success = Debug_Dump(output);
    // call your Debug_Dump logging your state number and output
    // 2) wait depending on state
    // 3) hard code this so input always shows all switches pressed
    // 4) next depends on state and input
  }
}
// use main5 to grade
int main5(void){// main5
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Grader_Init();  // execute this line before your code
  Traffic_Init(); // your Lab 4 initialization
  SysTick_Init(); // Initialize SysTick for software waits
  Debug_Init();
  uint32_t i=southG;// initialize your FSM
  uint32_t input;
  uint32_t output;
  uint32_t success;
  Lab4Grader(1); // activate UART, grader and interrupts
  while(1){
      input =7;
      output = Traffic_Out(input);
      success = Debug_Dump(output);
    // 1) output depending on state using Traffic_Out
    // call your Debug_Dump logging your state number and output
    // 2) wait depending on state

      input = Traffic_In();// 3) input from switches
    // 4) next depends on state and input
  }
}

