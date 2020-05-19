/*-------------------------------------
 temporizadores.c
-------------------------------------*/

#include "defines.h"
#include "sprites.h"
#include <nds.h>
#include <stdio.h>
#include "fondos.h"

// Attention routine to timer interruption
int contador; // Counter of the timer
int estado;   // Status assigned to the background
void IntTemp() {
	if(estado == PRADO){
		contador++;
		if(contador == 15){
			estado = DESIERTO;
			contador = 0;
		}
	}
	else if(estado == DESIERTO){
		contador++;
		if(contador == 15){
			estado = CARRETERA;
			contador = 0;
		}
	}
	else if(estado == CARRETERA){
		contador++;
		if(contador == 15){
			estado = FINAL;
			contador = 0;
		}
	}
}
