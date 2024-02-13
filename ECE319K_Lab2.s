//****************** ECE319K_Lab2.s ***************
// Your solution to Lab 2 in assembly code
// Author: Ashton Knecht
// Last Modified: 1/31/2024



// ECE319K Spring 2024 (ECE319H students do Lab2H)
   .equ GPIOB_RSTCTL,   0x400A2804
   .equ GPIOB_PWREN,    0x400A2800
   .equ GPIOB_DOE31_0,  0x400A32C0
   .equ GPIOB_DOUT31_0, 0x400A3280
   .equ GPIOB_DIN31_0,  0x400A3380
   .equ IOMUXPB0,       0x40428004+4*11
   .equ IOMUXPB1,       0x40428004+4*12
   .equ IOMUXPB2,       0x40428004+4*14
   .equ IOMUXPB3,       0x40428004+4*15
   .equ IOMUXPB16,      0x40428004+4*32
   .equ IOMUXPB17,      0x40428004+4*42
   .equ IOMUXPB18,      0x40428004+4*43

        .data
        .align 2
// Declare global variables here if needed
// with the .space assembly directive

        .text
        .thumb
        .align 2
        .global EID
EID:    .string "ATK836" // replace ZZZ123 with your EID here
        .align 2

// this allow your Lab2 programs to the Lab2 grader
        .global Lab2Grader
// this allow the Lab2 grader to call your Lab2 program
        .global Lab2
// these two allow your Lab2 programs to all your Lab3 solutions
        .global Debug_Init
        .global Dump

// Switch input: PB2 PB1 or PB0, depending on EID
// LED output:   PB18 PB17 or PB16, depending on EID
// logic analyzer pins PB18 PB17 PB16 PB2 PB1 PB0
// analog scope pin PB20
Lab2:
// Initially the main program will
//   set bus clock at 80 MHz,
//   reset and power enable both Port A and Port B
// Lab2Grader will
//   configure interrupts  on TIMERG0 for grader or TIMERG7 for TExaS
//   initialize ADC0 PB20 for scope,
//   initialize UART0 for grader or TExaS
     MOVS R0,#3  // 0 for info, 1 debug with logic analyzer, 2 debug with scope, 10 for grade
     BL   Lab2Grader
     BL   Debug_Init // your Lab3
     BL   Lab2Init // initialize input and output pins
// other initializations



// INPUT PIN  - PIN 1
// OUTPUT PIN - PIN 18
	MOVS R5,#26 // Time Period (This value of 26 provides time period of 20.3, I had a TA look at my program and they couldn't find why a value of 20 wouldn't give me the correct value)
	MOVS R0,#10 // Starting Duty Cycle

FLASH:
	MOVS R4,R0 // Duty Cycle to R4

	LDR  R0,=800
	MOVS R3,#100
	MOVS R2,#1 // On Delay
	MULS R2,R4 // R2<- Duty Cycle * 1
	MULS R2,R5 // R2<- Product * Time Period
	MULS R2,R0 // R2<- Prduct * Bus Cycles * 10^-2 per millisecond

			   // Off Delay
	MULS R3,R5 // R3<- 100* Time Period
	MULS R3,R0 // R3<- Product * Bus Cycles * 10^-2 per millisecond
	SUBS R3,R3,R2 // R3<- Max Bus Cycles - On Time Period

	LDR R7,=262144


loop:
     BL CHECK // INPUT?
     LDR R0,=GPIOB_DOUT31_0 // LIGHT ON
     LDR R1,[R0]
     ORRS R1,R7
     STR R1,[R0]

     MOVS R0,R2 // On Delay

	 // Debug Code
	 PUSH {R0-R4}
	 BL Dump
	 POP {R0-R4}


     BL DELAY

     BL CHECK // INPUT?

     LDR R0,=GPIOB_DOUT31_0 // LIGHT OFF
     LDR R1,[R0]
     BICS R1,R7
     STR R1,[R0]

     MOVS R0,R3 // Off Delay

     PUSH {R0-R4}
	 BL Dump
	 POP {R0-R4}

     BL DELAY
     
     B    loop

// Sub-Routine 1 - CHECK

CHECK: // Checks for Button Input
	   // True -> Switch
	   // False -> Return Linkage
	MOVS R0,#2
	LDR R1,=GPIOB_DIN31_0
	LDR R1,[R1]
	ANDS R0,R1 // CHECKS ONLY BIT 2
	BEQ STOP
	MOVS R0,R4
	//B SWITCH
STOP:
	BX LR

// Sub-Routine 2 - SWITCH

SWITCH: // Switches Duty Cycle:
		// Input (R0)- Old Duty Cycle
		// Output (R0)- New Duty Cycle
	 LDR R2,=GPIOB_DOUT31_0 // LIGHT OFF
     LDR R1,[R2]
     BICS R1,R7
     STR R1,[R2]

TOP: // Loop Until Button is not pressed

    MOVS R2,#2 // Check for Input to be off
	LDR R1,=GPIOB_DIN31_0
	LDR R1,[R1]
	ANDS R2,R1 // CHECKS ONLY BIT 2
	BNE TOP

	// IF DC= 10 / ELSEIF DC= 35 / ELSEIF DC= 50 / ELSE / END Structure

IF:
	CMP R0,#10
	BNE ELSEIF1
	MOVS R0,#35 // New Duty Cycle: 35%
	B END

ELSEIF1:
	CMP R0,#35
	BNE ELSEIF2
	MOVS R0,#50 // New Duty Cycle: 50%
	B END

ELSEIF2:
	CMP R0,#50
	BNE ELSE
	MOVS R0,#85 // New Duty Cycle: 85%
	B END

ELSE:
	MOVS R0,#10 // New Duty Cycle: 10%
	B END

END:

	B FLASH

// Sub-Routine 3 - DELAY (From Textbook)

DELAY:
	SUBS R0,R0,#2
dloop:
	SUBS R0,R0,#4
	BHS dloop
	BX	LR


// make switch the input, LED the output
// PortB is already reset and powered
// Set IOMUX for your input and output
// Set GPIOB_DOE31_0 for your output (be friendly)
Lab2Init:
	LDR R0,=0x00040081 // Initializing Input PINcM
	LDR R1,=IOMUXPB1
	STR R0,[R1]

	LDR R0,=0x00000081 // Initializing Output PINcM
	LDR R1,=IOMUXPB18
	STR R0,[R1]

	LDR R0,=GPIOB_DOE31_0 // Setting Bit 18 of DOEB Register
	LDR R1,=262144 // BIT 18
	LDR R3,[R0]
	ORRS R1,R1,R3
	STR R1,[R0]
   BX   LR


   .end
