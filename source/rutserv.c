/*-------------------------------------
 rutserv.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "teclado.h"
#include "defines.h"
#include "temporizadores.h"

// This procedure initializes the interrupt table so that the interrupt manager knows
// what attention routine you have to execute when an interruption request arrives.
// It is also here where the peripheral control registers are configured.

void HabilitarInterrupciones() 
{ 	
  // In the Interrupt Controller
  // All interrupts are inhibited first
	DisableInts();
 
  // Write a 1 in the corresponding bit
   	IE = IE | 0x1008; //ACTIVATE 12 and 3 //0001000000001000
  // All interrupts are re-enabled   
	EnableInts();
}

void ProgramarRegistrosControl() 
{ 
  	// Keyboard Control Record
  	TECLAS_CNT= 0x400C; //SELECT and START, bits 2 and 3 //0100000000001100
  	// TIMER0_CNT   
	TIMER0_CNT=0xC3;//11000011 Frequency 1 overflow per second
  	//   	The timer is activated by putting a 1 in the 7th bit.
  	//   	The timer will interrupt when the counter overflows, 
  	//   	if there is a 1 in the 6th bit.
  	//   The two bits of least weight indicate the following:
  	//      00 frequency 33554432 hz
  	//      01 frequency 33554432/64 hz
  	//      10 frequency 33554432/256 hz
  	//      11 frequency 33554432/1024 hz
    
  	// TIMER0_DAT 
  	//   Indicates what value to start counting from (latch)
   	TIMER0_DAT=32768;  
}

void DefinirVectorInterrupciones() 
{ 
 	// Attention routines
	// Keyboard Attention Routine
	irqSet (IRQ_KEYS, IntTec);
  	// Timers Attention Routines
	irqSet (IRQ_TIMER0 , IntTemp);
}

void InhibirInterrupciones() 
{ 
	// In the Interrupt Controller
  	// All interrupts are inhibited first
    	DisableInts();
  	// Write a 0 in the corresponding bit
	IE = IE | 0XEFF7; //TO TURN OFF 12 Y 3
  	// All interrupts are re-enabled
	EnableInts();
}


void interrupciones() //This void set scheduled interrupts on main()
{
  	HabilitarInterrupciones();
  	ProgramarRegistrosControl();
  	DefinirVectorInterrupciones();
}
