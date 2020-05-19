/*-------------------------------------
defines.h
-------------------------------------*/

#include <nds.h>
#include <stdio.h>

// Here you define the interrupt manager logs
#define IME		(*(vuint16*)0x04000208) //Interrupt Master Enable - Enable or disable all interrupts
#define IE		(*(vuint32*)0x04000210) //Interrupt Enable - Turn interrupts on or off one by one
#define IF		(*(vuint32*)0x04000214) //Interrupt Flag - Save interrupt requests

// Here some functions are defined for the treatment of interruptions
#define EnableInts() 	IME=1 //Enable all interrupts
#define DisableInts() 	IME=0 //Disable all interrupts

// Here the keyboard registers are defined 
#define TECLAS_DAT	(*(vuint16*)0x4000130) //Keyboard data recording
#define TECLAS_CNT	(*(vuint16*)0x4000132) //Keyboard control register

// Here the timer registers are defined
#define TIMER0_CNT   	(*(vuint16*)0x04000102) //Timer control register
// The timer is activated by putting a 1 in the 7th bit.
// The timer will interrupt when the counter overflows, if there is a 1 in the 6th bit.
// The two bits of least weight indicate the following:
//		00 frequency 33554432 hz
//		01 frequency 33554432/64 hz
//		10 frequency 33554432/256 hz
//		11 frequency 33554432/1024 hz

#define TIMER0_DAT    (*(vuint16*)0x04000100) //Timer data recording
//It is used to indicate from what value it has to start counting

// In order not to get involved with the numbers, each key has been assigned a name

#define A		0 
#define B		1
#define SELECT		2 
#define START		3
#define IZDA		4 
#define DCHA		5
#define ARRIBA		6 
#define ABAJO		7
#define R		8 
#define L		9

// Assign a name to each state
#define INICIO 0    		//STATE 0
#define PRADO 1			//STATE 1
#define DESIERTO 2		//STATE 2
#define CARRETERA 3		//STATE 3
#define FINAL 4			//STATE 4
#define WALK_DOWN 0    		//STATE OF MOVEMENT 0
#define WALK_UP 1  		//STATE OF MOVEMENT 1
#define WALK_LEFT 2    		//STATE OF MOVEMENT 2
#define WALK_RIGHT 3   		//STATE OF MOVEMENT 3

//Global variables
extern int contador;
extern int estado;
extern int estadoSoldado;
extern int documentos;
extern bool posicionar;

