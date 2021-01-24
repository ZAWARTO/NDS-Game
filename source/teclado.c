/*-------------------------------------
 teclado.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "defines.h"
#include "sprites.h"
#include "fondos.h"

// Return values assigned to the NDS keys, if none is pressed, returns -1
int  TeclaPulsada() 
{
   	// Values: 
   	// A=0; B=1; Select=2; Start=3; Der=4; Izq=5;
   	// Arriba=6; Abajo=7; R=8; L=9;
   	// -1 en otros casos

	if((~TECLAS_DAT & 0x01)!= 0)return A;
	else if((~TECLAS_DAT & 0x02)!= 0)return B;
	else if((~TECLAS_DAT & 0x04)!= 0)return SELECT;
	else if((~TECLAS_DAT & 0x08)!= 0)return START;
	else if((~TECLAS_DAT & 0x10)!= 0)return DCHA;
	else if((~TECLAS_DAT & 0x20)!= 0)return IZDA;
	else if((~TECLAS_DAT & 0x40)!= 0)return ARRIBA;
	else if((~TECLAS_DAT & 0x80)!= 0)return ABAJO;
	else if((~TECLAS_DAT & 0x100)!= 0)return R;
	else if((~TECLAS_DAT & 0x200)!= 0)return L;
	else return -1;
}

int contador;
int estado;
int tecla;
int documentos;
bool posicionar;
// Attention routine to keyboard interruptions
void IntTec() {
	tecla = TeclaPulsada();
	if(tecla == START && estado == INICIO)
	{
		posicionar = true;
		MostrarPRADO();
		estado=PRADO;
	}

	if(tecla == SELECT && estado == FINAL)
	{
		MostrarINICIO();
		estado = INICIO;
		documentos = 0;	
	}
}
