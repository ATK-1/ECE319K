// Lab9Main.c
// Runs on MSPM0G3507
// Lab 9 ECE319K
// Ashton Knecht and Luis Aceves
// Last Modified: 12/31/2023

#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/ADC1.h"
#include "../inc/DAC5.h"
#include "SmallFont.h"
#include "LED.h"
#include "Switch.h"
#include "Sound.h"
#include "images/images.h"
#include "List.h"






// ****note to ECE319K students****
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz


list_t Deck_List;
list_t User_List;
list_t Opp_List;

list_node_t ListNodes[112];
card_t Cards[112];

const char soundCardDown [3540] = {16,16,16,16,15,15,15,15,15,16,16,15,16,16,16,15,16,16,16,16,16,16,16,16,15,15,15,15,16,16,16,16,16,16,16,15,16,16,16,16,16,16,15,16,16,16,16,16,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,15,15,15,16,15,16,16,16,16,15,15,15,16,16,16,16,16,16,16,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,16,16,16,16,15,15,15,15,15,15,16,16,16,16,16,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,15,16,16,16,16,15,15,15,15,15,15,15,15,15,15,15,15,16,15,15,15,15,15,15,16,15,15,15,15,15,15,15,16,16,15,15,15,16,15,15,15,16,16,16,16,16,15,15,15,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,15,15,15,15,15,15,16,16,16,15,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,16,16,16,16,16,15,15,15,15,15,16,16,16,16,16,16,16,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,16,16,16,15,15,15,16,16,16,16,16,15,15,15,16,16,15,15,16,16,16,15,15,15,15,16,16,15,15,15,15,16,16,16,15,15,16,16,16,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,16,16,16,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,15,16,16,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,16,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,15,15,15,16,16,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,15,15,15,15,15,16,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,15,15,15,15,15,15,15,15,15,15,15,16,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,15,16,16,15,16,16,16,16,16,15,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,15,15,15,15,15,15,16,15,15,15,15,16,16,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,16,16,16,16,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,15,15,15,16,16,15,15,15,16,16,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,15,15,15,15,15,15,15,15,15,15,15,16,16,15,15,15,15,15,15,15,15,16,16,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,15,15,15,16,16,16,16,15,15,15,15,15,15,15,15,16,16,16,15,15,15,15,15,15,15,15,15,15,15,15,16,16,16,15,15,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,15,15,16,16,16,16,16,16,16,16,15,15,15,16,16,16,16,15,15,16,16,16,15,16,16,15,15,16,15,15,15,15,15,16,16,16,16,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,16,16,15,15,15,15,15,15,15,15,15,15,15,15,15,16,15,15,15,15,15,15,15,15,16,16,16,16,16,16,15,15,16,16,16,15,15,16,16,16,16,16,15,15,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,15,16,16,16,16,16,16,15,16,16,16,16,16,16,16,16,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,15,16,16,15,15,16,16,16,16,16,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,16,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,15,15,15,15,16,16,16,16,16,15,15,15,15,16,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,16,16,16,16,16,16,16,16,15,15,15,15,15,16,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,15,15,15,15,15,16,16,16,15,16,16,16,15,15,15,16,15,16,16,15,15,15,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,16,16,15,16,16,16,16,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,16,15,15,15,15,15,16,16,16,16,16,16,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,17,17,17,16,16,16,16,16,16,17,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,15,15,15,15,15,15,15,15,15,14,14,15,15,15,15,15,14,14,14,14,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,16,17,17,17,17,17,17,17,17,17,17,17,17,16,16,16,17,17,17,16,16,16,16,16,16,16,16,16,16,15,15,15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,13,13,14,14,13,13,13,13,13,13,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,16,15,15,16,16,16,16,16,16,16,16,16,17,17,17,17,17,17,17,17,17,17,17,18,18,18,17,17,17,18,18,18,17,17,17,17,17,17,18,18,18,18,17,18,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,16,16,16,16,16,16,16,16,16,15,15,15,15,15,15,15,15,15,14,14,14,14,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,13,13,13,13,13,13,13,13,13,13,13,14,14,14,14,14,14,15,14,14,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,16,16,17,17,16,17,17,17,17,17,17,17,17,17,17,17,16,16,16,16,17,17,16,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,18,18,17,18,18,17,17,17,17,17,17,17,17,17,17,16,16,16,16,16,16,16,16,16,16,16,15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,13,13,13,13,13,13,13,12,13,13,13,13,13,13,13,13,13,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,17,17,17,17,17,16,16,17,17,17,17,16,17,17,16,17,17,17,17,17,17,17,17,17,17,17,17,18,18,18,17,17,18,17,17,17,17,17,17,17,17,17,17,17,16,16,16,16,16,15,15,16,15,15,15,15,15,15,15,16,16,15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,13,13,13,13,13,13,14,14,13,13,13,13,13,13,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,16,16,15,15,16,16,16,16,16,16,16,17,17,17,17,17,17,17,16,16,16,16,17,16,16,17,16,16,17,17,17,17,17,17,17,17,18,17,17,18,18,18,18,18,18,18,18,18,18,17,17,17,17,17,17,17,17,17,17,16,16,16,16,16,16,16,15,15,15,14,14,14,14,14,14,14,14,14,14,14,13,13,13,13,13,14,14,14,13,13,13,13,13,13,13,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,16,16,16,16,17,17,17,17,17,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,17,17,17,17,17,17,16,16,16,15,15,15,15,15,15,15,15,15,14,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,14,14,14,14,13,14,14,14,14,13,13,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,16,16,16,16,16,16,16,16,16,16,16,17,17,17,17,17,17,17,17,17,17,17,17,18,17,17,17,17,17,18,18,18,18,18,17,17,17,17,17,17,17,16,16,16,16,16,16,16,16,15,16,16,16,16,15,15,15,15,15,15,16,15,15,15,15,15,15,14,14,15,15,15,15,16,15,15,14,14,14,14,14,13,13,14,14,14,14,15,15,15,15,15,15,15,15,15,15,15,15,16,15,15,16,15,15,15,15,15,15,16,16,16,16,15,16,16,16,17,17,17,17,16,16,16,16,16,16,17,17,17,17,17,16,17,17,17,17,17,16,16,16,16,15,15,15,15,15,14,14,15,14,15,16,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,15,14,14,14,15,14,14,14,14,14,15,15,14,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,16,15,16,16,16,16,17,17,17,18,17,17,17,17,17,17,17,17,17,17,17,16,17,17,17,18,18,17,18,18,18,17,18,19,19,18,18,18,18,18,18,18,18,18,18,18,17,17,17,17,17,17,17,16,16,15,15,15,15,15,15,14,14,14,14,14,14,14,15,15,14,13,13,13,13,13,13,14,13,13,13,13,12,12,12,13,13,13,13,13,12,12,12,12,12,13,13,12,13,13,13,13,13,14,14,14,14,14,14,14,14,15,15,15,15,15,15,16,15,15,15,16,16,16,16,16,16,17,17,17,17,17,17,18,18,18,19};

// Function Declarations
void discard(struct list_node* removed_node);
void draw(struct list* player_hand, struct list_node* card_node);
void draw_seven(void);
uint32_t random_index(void);
list_node_t* traverse_index(list_t* deck, uint32_t index);

uint32_t *soundPointer;





void PLL_Init(void){ // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0);   // run this line for 80MHz
}

uint32_t M=1;
uint32_t Random32(void){
  M = 1664525*M+1013904223;
  return M;
}
uint32_t Random(uint32_t n){
  return (Random32()>>16)%n;
}


// games  engine runs at 30Hz
void TIMG12_IRQHandler(void){uint32_t pos,msg;
  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
// game engine goes here
    // 1) sample slide pot
    // 2) read input switches
    // 3) move sprites
    // 4) start sounds
    // 5) set semaphore
    // NO LCD OUTPUT IN INTERRUPT SERVICE ROUTINES
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
  }
}
uint8_t TExaS_LaunchPadLogicPB27PB26(void){
  return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
}

typedef enum {English, Spanish, Portuguese, French} Language_t;
Language_t myLanguage=English;
typedef enum {HELLO, GOODBYE, LANGUAGE} phrase_t;
const char Hello_English[] ="Hello";
const char Hello_Spanish[] ="\xADHola!";
const char Hello_Portuguese[] = "Ol\xA0";
const char Hello_French[] ="All\x83";
const char Goodbye_English[]="Goodbye";
const char Goodbye_Spanish[]="Adi\xA2s";
const char Goodbye_Portuguese[] = "Tchau";
const char Goodbye_French[] = "Au revoir";
const char Language_English[]="English";
const char Language_Spanish[]="Espa\xA4ol";
const char Language_Portuguese[]="Portugu\x88s";
const char Language_French[]="Fran\x87" "ais";
const char *Phrases[3][4]={
  {Hello_English,Hello_Spanish,Hello_Portuguese,Hello_French},
  {Goodbye_English,Goodbye_Spanish,Goodbye_Portuguese,Goodbye_French},
  {Language_English,Language_Spanish,Language_Portuguese,Language_French}
};
// use main1 to observe special characters
int main1(void){ // main1
    char l;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
  ST7735_FillScreen(0x0000);            // set screen to black
  for(phrase_t myPhrase=HELLO; myPhrase<= GOODBYE; myPhrase++){
    for(Language_t myL=English; myL<= French; myL++){
         ST7735_OutString((char *)Phrases[LANGUAGE][myL]);
      ST7735_OutChar(' ');
         ST7735_OutString((char *)Phrases[myPhrase][myL]);
      ST7735_OutChar(13);
    }
  }
  Clock_Delay1ms(3000);
  ST7735_FillScreen(0x0000);       // set screen to black
  l = 128;
  while(1){
    Clock_Delay1ms(2000);
    for(int j=0; j < 3; j++){
      for(int i=0;i<16;i++){
        ST7735_SetCursor(7*j+0,i);
        ST7735_OutUDec(l);
        ST7735_OutChar(' ');
        ST7735_OutChar(' ');
        ST7735_SetCursor(7*j+4,i);
        ST7735_OutChar(l);
        l++;
      }
    }
  }
}

// use main2 to observe graphics
int main2(void){ // main2
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_BLACK);
  ST7735_DrawBitmap(22, 159, PlayerShip0, 18,8); // player ship bottom
  ST7735_DrawBitmap(53, 151, Bunker0, 18,5);
  ST7735_DrawBitmap(42, 159, PlayerShip1, 18,8); // player ship bottom
  ST7735_DrawBitmap(62, 159, PlayerShip2, 18,8); // player ship bottom
  ST7735_DrawBitmap(82, 159, PlayerShip3, 18,8); // player ship bottom
  ST7735_DrawBitmap(0, 9, SmallEnemy10pointA, 16,10);
  ST7735_DrawBitmap(20,9, SmallEnemy10pointB, 16,10);
  ST7735_DrawBitmap(40, 9, SmallEnemy20pointA, 16,10);
  ST7735_DrawBitmap(60, 9, SmallEnemy20pointB, 16,10);
  ST7735_DrawBitmap(80, 9, SmallEnemy30pointA, 16,10);

  for(uint32_t t=500;t>0;t=t-5){
    SmallFont_OutVertical(t,104,6); // top left
    Clock_Delay1ms(50);              // delay 50 msec
  }
  ST7735_FillScreen(0x0000);   // set screen to black
  ST7735_SetCursor(1, 1);
  ST7735_OutString("GAME OVER");
  ST7735_SetCursor(1, 2);
  ST7735_OutString("Nice try,");
  ST7735_SetCursor(1, 3);
  ST7735_OutString("Earthling!");
  ST7735_SetCursor(2, 4);
  ST7735_OutUDec(1234);
  while(1){
  }
}

// use main3 to test switches and LEDs
int main3(void){ // main3
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  while(1){
    // write code to test switches and LEDs
    
  }
}
// use main4 to test sound outputs
int main4(void){ uint32_t last=0,now;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  Sound_Init(1,1);  // initialize sound
  TExaS_Init(ADC0,6,0); // ADC1 channel 6 is PB20, TExaS scope
  __enable_irq();
  while(1){
    now = Switch_In(); // one of your buttons
    if((last == 0)&&(now == 1)){
      Sound_CardDown(); // call one of your sounds
    }
    if((last == 0)&&(now == 2)){
      Sound_CardDown(); // call one of your sounds
    }
    if((last == 0)&&(now == 4)){
      Sound_CardDown(); // call one of your sounds
    }
    if((last == 0)&&(now == 8)){
      Sound_CardDown(); // call one of your sounds
    }
    // modify this to test all your sounds
  }
}
// ALL ST7735 OUTPUT MUST OCCUR IN MAIN
int main5(void){ // final main
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_BLACK);
  ADCinit();     //PB18 = ADC1 channel 5, slidepot
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  Sound_Init(1,1);  // initialize sound
  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
    // initialize interrupts on TimerG12 at 30 Hz
  TimerG12_IntArm(80000000/30,2);
  // initialize all data structures
  __enable_irq();

  while(1){
    // wait for semaphore
       // clear semaphore
       // update ST7735R
    // check for end game or level switch
  }
}








// Function Definitions -

void discard(list_node_t* removed_node){
    if(removed_node->card_pointer->in_deck == user){
        list_remove(&User_List,removed_node); // Remove From User's Hand
    }
    if(removed_node->card_pointer->in_deck == opp){
        list_remove(&Opp_List,removed_node); // Remove From Opponent's Hand
    }
    removed_node->card_pointer->in_deck= dis; // Symbolizes Discarded

    list_add(&Deck_List,removed_node); // Adding to the Back of the Deck (Where Discards are held)
}

void draw(list_t* player_hand, list_node_t* card_node){
    if(player_hand->id == user){
        card_node->card_pointer->in_deck= user ; // Sent to User's Hand
    }
    if(player_hand->id == opp){
            card_node->card_pointer->in_deck= opp; // Sent to Opponent's Hand
        }
    list_remove(&Deck_List,card_node); // Removes Card From Deck
    list_add(player_hand,card_node); // Adds Card to Player Hand
}


void game_init(void){
    list_init(&Deck_List);
    list_init(&User_List);
    list_init(&Opp_List);
    uint32_t index=0;
    for(uint8_t color=0; color<= 3 ; color++){
        for(uint8_t value=0; value<=9; value++){

            Cards[index].value= value; // Init Card
            Cards[index].color = color;
            Cards[index].in_deck = deck;
            Cards[index].power = 0;
            ListNodes[index].card_pointer = &Cards[index]; // Init Node
            list_add(&Deck_List, &ListNodes[index]); // Add to Deck
            index++;

            Cards[index].value= value; // Init Card
            Cards[index].color = color;
            Cards[index].in_deck = deck;
            Cards[index].power = 0;
            ListNodes[index].card_pointer = &Cards[index]; // Init Node
            list_add(&Deck_List, &ListNodes[index]); // Add to Deck
            index++;
        }
        Cards[index].value= 10; // Skip
        Cards[index].color = color;
        Cards[index].in_deck = deck;
        Cards[index].power = 1;
        ListNodes[index].card_pointer = &Cards[index];
        list_add(&Deck_List, &ListNodes[index]);
        index++;

        Cards[index].value= 10; // Skip
        Cards[index].color = color;
        Cards[index].in_deck = deck;
        Cards[index].power = 1;
        ListNodes[index].card_pointer = &Cards[index];
        list_add(&Deck_List, &ListNodes[index]);
        index++;

        Cards[index].value= 11; // Reverse
        Cards[index].color = color;
        Cards[index].in_deck = deck;
        Cards[index].power = 1;
        ListNodes[index].card_pointer = &Cards[index]; // Init Node
        list_add(&Deck_List, &ListNodes[index]);
        index++;

        Cards[index].value= 11; // Reverse
        Cards[index].color = color;
        Cards[index].in_deck = deck;
        Cards[index].power = 0;
        ListNodes[index].card_pointer = &Cards[index]; // Init Node
        list_add(&Deck_List, &ListNodes[index]);
        index++;

        Cards[index].value= 12; // Reverse
        Cards[index].color = color;
        Cards[index].in_deck = deck;
        Cards[index].power = 2;
        ListNodes[index].card_pointer = &Cards[index]; // Init Node
        list_add(&Deck_List, &ListNodes[index]);
        index++;

        Cards[index].value= 12; // +2
        Cards[index].color = color;
        Cards[index].in_deck = deck;
        Cards[index].power = 2;
        ListNodes[index].card_pointer = &Cards[index]; // Init Node
        list_add(&Deck_List, &ListNodes[index]);
        index++;
    }

    for(uint32_t increment=0; increment<4; increment++){
        Cards[index].value= 13; // Wild
        //Cards[index].color = color;
        Cards[index].in_deck = deck;
        Cards[index].power = 3;
        ListNodes[index].card_pointer = &Cards[index]; // Init Node
        list_add(&Deck_List, &ListNodes[index]);
        index++;

        Cards[index].value= 13; // Wild +4
        //Cards[index].color = color;
        Cards[index].in_deck = deck;
        Cards[index].power = 4;
        ListNodes[index].card_pointer = &Cards[index]; // Init Node
        list_add(&Deck_List, &ListNodes[index]);
        index++;
    }


}


void draw_seven(void){ // This command assumes that this computer has priority in the reset - Should be only called by one computer
    uint32_t randomindex;
    list_node_t* card_node;
    uint32_t test=0;
    for(uint32_t counter=0; counter<7; counter++){


         //Draw for User

         randomindex = random_index();        // 0 <= randomindex <= Deck_List.length - 1
         card_node = traverse_index(&Deck_List, randomindex);
         draw(&User_List, card_node); // Place one random card into the user's hand
         //Output to UART

         //Wait some bus cycles so that we don't over fill the Transmit FIFO

         //Draw for Opponent

         randomindex = random_index();        // 0 <= random_index <= Deck_List.length - 1
         card_node = traverse_index(&Deck_List, randomindex);
         draw(&Opp_List, card_node); // Place one random card into the user's hand
         //Output to UART

         // Wait bus cycles


    }
}

uint32_t random_index(void){
    static uint32_t seed=0;
    if(seed==0){
        seed = ADCin();
    }
    seed = 1664525*seed+1013904223;
    return (seed>>16)%Deck_List.length;

}

list_node_t* traverse_index(list_t* deck, uint32_t index){
    uint32_t fail=0;
    list_node_t* node_pointer = deck->head;

    while(index != 0){
        if(node_pointer == Deck_List.tail){
            fail++;
        }
        node_pointer = list_traverse(node_pointer);
        index--;
    }
    return node_pointer;
}






int main6(void){ // Main 6 Testing game_init
    PLL_Init(); // set bus speed
    LaunchPad_Init();
    game_init();
    list_node_t* node;
    uint8_t card_value;
    uint8_t card_color;
    while(1){
        node= Deck_List.head;
        for(uint32_t index=0; index<112; index++){
            card_value = node->card_pointer->value;
            card_color = node->card_pointer->color;
            node = list_traverse(node);
        }
    }
}



int main7(void){ // Main 7 Testing Random Index
    PLL_Init(); // set bus speed
    LaunchPad_Init();
    ADCinit();
    game_init();
    uint32_t output1=0;
    while(1){
        if (Deck_List.length < 5){
            Deck_List.length = 112;
        }
        output1 = random_index();
        Deck_List.length--;
    }


}

int main(void){ // Main 8 Testing Draw 7
    PLL_Init(); // set bus speed
    LaunchPad_Init();
    ADCinit();
    game_init();
    draw_seven();
    while(1){

    }
}

