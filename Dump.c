// Dump.c
// Your solution to ECE319K Lab 3 Spring 2024
// Author: Your name
// Last Modified: Your date


#include <ti/devices/msp/msp.h>
#include "../inc/Timer.h"
#define MAXBUF 50
uint32_t DataBuffer[MAXBUF];
uint32_t TimeBuffer[MAXBUF];
uint32_t DebugCnt; // 0 to MAXBUF (0 is empty, MAXBUF is full)

// *****Debug_Init******
// Initializes your index or pointer.
// Input: none
// Output:none
void Debug_Init(void){
// students write this for Lab 3
// This function should also initialize Timer G12, call TimerG12_Init.
    DebugCnt=0;
    TimerG12_Init();
}

// *****Debug_Dump******
// Records one data and one time into the two arrays.
// Input: data is value to store in DataBuffer
// Output: 1 for success, 0 for failure (buffers full)
uint32_t Debug_Dump(uint32_t data){
// students write this for Lab 3
// The software simply reads TIMG12->COUNTERREGS.CTR to get the current time in bus cycles.
    if(DebugCnt>= MAXBUF){ // Check if Buffer is Full
        return 0; // True? Return 0
    }
    DataBuffer[DebugCnt]= data; // Dump Data
    TimeBuffer[DebugCnt]= TIMG12->COUNTERREGS.CTR; // Dump Time
    DebugCnt++; // Increment Count
    return 1; // success

}
// *****Debug_Dump2******
// Always record data and time on the first call to Debug_Dump2
// However, after the first call
//    Records one data and one time into the two arrays, only if the data is different from the previous call.
//    Do not record data or time if the data is the same as the data from the previous call
// Input: data is value to store in DataBuffer
// Output: 1 for success (saved or skipped), 0 for failure (buffers full)
uint32_t Debug_Dump2(uint32_t data){
// optional for Lab 3
// The software simply reads TIMG12->COUNTERREGS.CTR to get the current time in bus cycles.

    if(DataBuffer[DebugCnt-1]==data){ // Check if Value is Same
        return 1;
    } // True? Return 1
    if(DebugCnt>= MAXBUF){ // Check if Buffer is Full
        return 0; // True? Return 0
    }
    DataBuffer[DebugCnt]= data; // Dump Data
    TimeBuffer[DebugCnt]= TIMG12->COUNTERREGS.CTR; // Dump Time
    DebugCnt++; // Increment Count
    return 1; // success

}
// *****Debug_Period******
// Calculate period of the recorded data using mask
// Input: mask specifies which bit(s) to observe
// Output: period in bus cycles
// Period is defined as rising edge (low to high) to the next rising edge.
// Return 0 if there is not enough collected data to calculate period .
uint32_t Debug_Period(uint32_t mask){
// students write this for Lab 3
// This function should not alter the recorded data.
// AND each recorded data with mask,
//    if nonzero the signal is considered high.
//    if zero, the signal is considered low.

    uint32_t firsttime=0; // Initializations
    uint32_t lasttime=0;
    uint32_t counter=0;
    uint8_t firsttimeset=0;
    uint8_t concurrent=0;
    for(uint8_t index2=0;index2<DebugCnt; index2++){ // Loop through DataBuffer
        if(0 != (DataBuffer[index2]&mask)){ // Is it high?
            if(firsttimeset==0){ // Is firsttime determined?
                firsttime=TimeBuffer[index2];
                firsttimeset=1;
                concurrent=1; // Subsequent high's are not rising edge
            }
            if(concurrent==0){
                lasttime=TimeBuffer[index2];
                counter++; // Number of Time Periods
                concurrent=1;
            }
        }
        else{
            concurrent=0;
        }
    }
    if(lasttime==0){ // No full Time Period
        return lasttime;// Fail
    }
return ((firsttime-lasttime)/counter); // Average Time Period
}



// *****Debug_Duty******
// Calculate duty cycle of the recorded data using mask
// Input: mask specifies which bit(s) to observe
// Output: period in percent (0 to 100)
// Period is defined as rising edge (low to high) to the next rising edge.
// High is defined as rising edge (low to high) to the next falling edge.
// Duty cycle is (100*High)/Period
// Return 0 if there is not enough collected data to calculate duty cycle.
uint32_t Debug_Duty(uint32_t mask){
// optional for Lab 3
// This function should not alter the recorded data.
// AND each recorded data with mask,
//    if nonzero the signal is considered high.
//    if zero, the signal is considered low.
    uint32_t firsttime=0; // Initializations
    uint32_t lasttime=0;
    uint32_t counter=0;
    uint8_t firsttimeset=0;
    uint8_t concurrent=0;
    uint32_t timeon;
    for(uint8_t index2=0;index2<DebugCnt; index2++){ // Loop through DataBuffer
        if(0 != (DataBuffer[index2]&mask)){ // Is it high?
            if(index2!=DebugCnt){
                timeon=timeon+(TimeBuffer[index2]-TimeBuffer[index2+1]);
            }
            if(firsttimeset==0){ // Is firsttime determined?
                firsttime=TimeBuffer[index2];
                firsttimeset=1;
                concurrent=1; // Subsequent high's are not rising edge
            }
            if(concurrent==0){
                lasttime=TimeBuffer[index2];
                counter++; // Number of Time Periods
                concurrent=1;
            }
        }
        else{
            concurrent=0;
        }
    }
    if(lasttime==0){ // No full Time Period
        return lasttime;// Fail
    }
return (timeon/((firsttime-lasttime)/counter)); // Average Time Period
}



// Lab2 specific debugging code
uint32_t Theperiod;
void Dump(void){
  uint32_t out = GPIOB->DOUT31_0&0x0070000; // PB18-PB16 outputs
  uint32_t in = GPIOB->DIN31_0&0x0F;        // PB3-PB0 inputs
  uint32_t data = out|in;                   // PB18-PB16, PB3-PB0
  uint32_t result = Debug_Dump(data);       // calls your Lab3 function
  if(result == 0){ // 0 means full
    Theperiod = Debug_Period(1<<18);        // calls your Lab3 function
//   __asm volatile("bkpt; \n"); // breakpoint here
// observe Theperiod
  }
}




