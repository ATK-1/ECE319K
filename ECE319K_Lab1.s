//****************** ECE319K_Lab1.s ***************
// Your solution to Lab 1 in assembly code
// Author: Ashton Knecht - ATK 836
// Last Modified: 1/24/2024
// Spring 2024
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
        .global Phase
Phase:  .long 10// 0 for info, 1-6 for debug, 10 for grade

        .global Lab1
// Input: R0 points to the list
// Return: R0 as specified in Lab 1 assignment and terminal window
// According to AAPCS, you must save/restore R4-R7
// If your function calls another function, you must save/restore LR
Lab1: PUSH {R4-R7,LR}
       // your solution goes here

TOP:	LDR R1,=EID // R1= Pointer to EID
		LDR R2,[R0] // Load Loctaion [R0] into R2
		ADDS R2,#0
		BEQ	FAIL		// If R2 is Null, go to FAIL

LOOP:	LDRB R3,[R1] // Load Original Ascii Code
		ADDS R3,#0
		BEQ MATCH // If Null, go to MATCH
		LDRB R4,[R2] // Load New Ascii Code
		CMP R3,R4
		BNE SKIP
		ADDS R1,#1
		ADDS R2,#1// If same, incriment pointers
		B LOOP// LOOP

SKIP:	ADDS R0,#8 // ELSE Incriment List Pointer by 2
		B TOP// TOP

FAIL:	LDR R0,=-1 // Output -1
		B DONE

MATCH:	ADDS R0,#4 // Increment List Pointer by 1
		LDR R0,[R0] // Output Value at List Pointer


DONE:      POP  {R4-R7,PC} // Return


        .end
