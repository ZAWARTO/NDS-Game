
#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>       	
#include "fondos.h"
#include "sprites.h"
#include "defines.h"
#include "rutservs.h"
#include "teclado.h"
#include "temporizadores.h"
#include <spritesheet.h>	//Soldier sprite and the secret document
#include <maxmod9.h>		//maxmod9 sound handler library
#include "soundbank_bin.h"	//Generated by the compiler
#include "soundbank.h"		//Generated by the compiler

//-----------------------------------------------------
// Global variables
//-----------------------------------------------------
int tecla;		//Later TeclaPulsada() is asigned to this int
int contador;
int estado;
int estadoSoldado; 	//State of the soldier movement
int documentos;		//Documents collected
bool posicionar;	//True if the game needs to set up the position of the sprites
//-----------------------------------------------------
// Sprite data structures
//-----------------------------------------------------

//Data structure that defines the position of the soldier's sprite and its corresponding frame
typedef struct 
{
	int x, y; 	// soldier x and y position
	u16* gfx; 	// gfx of oam
	u8* gfx_frame;
} Soldado;

//Data structure that defines the position of the document sprite and its corresponding frame
typedef struct 
{
	int x, y;	// document x and y position
	u16* gfx;	// gfx of oam
	u8* gfx_frame;
} Documento;

//---------------------------------------------------------------------------------
// Movement code by survey for the soldier
//---------------------------------------------------------------------------------
void movimientoSoldado(Soldado * soldado) 
{

	//Assignment of the global key variable to the pressed key function
	tecla = TeclaPulsada();

	if (tecla == DCHA) 
	{
		estadoSoldado = WALK_RIGHT;
		soldado->x++;
	} 
	else if (tecla == IZDA) 
	{
		estadoSoldado = WALK_LEFT;
		soldado->x--;
	} 
	else if (tecla == ABAJO) 
	{
		estadoSoldado = WALK_DOWN;
		soldado->y++;
	} 
	else if (tecla == ARRIBA) 
	{
		estadoSoldado = WALK_UP;
		soldado->y--;
	}

	//It is assigned a slice (partition) of the jpg spritesheet depending on the state of its movement since it is divided into 5 slices
	//of which 4 belong to the movement and another to the document
	int frame = estadoSoldado;
	u8* offset = soldado->gfx_frame + frame * 16*16;
	dmaCopy(offset, soldado->gfx, 16*16);

	//Sprite initialization
	oamSet(&oamMain,
		0, // oam entry id
		soldado->x, soldado->y, 		// soldier x and y position
		0, 15, 					// priority and palette
		SpriteSize_16x16, 			// size
		SpriteColorFormat_256Color,		// 256-bit color palette
		soldado->gfx, 				// gfx of oam
		-1, false, false, false, false, false);
}

//---------------------------------------------------------------------------------
// Code to generate the document
//---------------------------------------------------------------------------------
void respawnDocumento(Documento * documento_sprite) 
{
	//The sprite is assigned position 5 of the spritesheet when dividing it into five blocks of 16x16 bits since the fourth slice (partition)
	//corresponds to the document drawing
	u8* offset = documento_sprite->gfx_frame + 4 * 16*16;
	dmaCopy(offset, documento_sprite->gfx, 16*16);

	//Sprite initialization
	oamSet(&oamMain,
		1, // oam entry id
		documento_sprite->x, documento_sprite->y, 	// posición x e y del soldado
		0, 15, // priority, palette			// prioridad y paleta
		SpriteSize_16x16,				// tamaño
		SpriteColorFormat_256Color,			// paleta de color de 256 bits
		documento_sprite->gfx, // the oam gfx		// el gfx del oam
		-1, false, false, false, false, false);
}

//---------------------------------------------------------------------------------
// Code to detect the collision of the soldier sprite and the document
//---------------------------------------------------------------------------------
bool collisionDetected(Documento documento_sprite, Soldado soldado) 
{
	//Sprite dimensions, 5 slices of 16x16
	int soldadoWidth = 16;
	int soldadoHeight = 16;
	int documentoWidth = 16;
	int documentoHeight = 16;

	//Collider dimension assignments based on sprite position
	int soldadoLeft = soldado.x;
	int documentoLeft = documento_sprite.x;
	int soldadoRight = soldado.x + soldadoWidth;
	int documentoRight = documento_sprite.x + documentoWidth;
	int soldadoTop = soldado.y;
	int documentoTop = documento_sprite.y;
	int soldadoBottom = soldado.y + soldadoHeight;
	int documentoBottom = documento_sprite.y + documentoHeight;

	//This if returns true if they collide, it depends on if their dimensions contact and returns false if they don't collide
	if (soldadoLeft < documentoRight && 
		soldadoRight > documentoLeft && 
		soldadoTop < documentoBottom && 
		soldadoBottom > documentoTop) 
	{ 
    	return true;
	}
	return false;
}

int main() 
{
	//Initializing the sound memory and loading the file DAZZLER2.MOD which is the music of the game
	mmInitDefaultMem((mm_addr)soundbank_bin);
	mmLoad(MOD_DAZZLER2);

	// Variable initialization
	documentos = 0;
	contador = 0; 
	estado = INICIO;

	//  Start the 2D graphics engine.
    	powerOn(POWER_ALL_2D);

     	// Set the bottom screen as main, initialize the graphics system
     	// and configure the fund system.
    	lcdMainOnBottom();
    	initVideo();
    	initFondos();

	// Screen position variable
	touchPosition pos_pantalla;

    	// Show wallpapers. 
    	MostrarINICIO();

	// Initialize sprite memory and save sprites to it
	initSpriteMem();
	guardarSpritesEnMemoria();

	//Initialize soldier position and document
	Soldado soldado = {20, 20}; 
	Documento documento_sprite = {0, 0}; 

	// To be able to print on screen (trace)
	consoleDemoInit();

	// Initialize soldier sprite and save it to memory, cannot initialize in sprites.c
	//because it refers to the data structure created in the main
	soldado.gfx = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	soldado.gfx_frame = (u8*)spritesheetTiles; 
	dmaCopy(spritesheetPal, SPRITE_PALETTE, 512);

	// Initialize the document sprite and save it in memory, cannot initialize in sprites.c
	//because it refers to the data structure created in the main
	documento_sprite.gfx = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	documento_sprite.gfx_frame = (u8*)spritesheetTiles;
	
	//Initialize interruptions
	interrupciones();

	//-----------------------------------------------------
	// Variable initialization
	//-----------------------------------------------------
	documentos = 0;
	contador = 0; 
	estado = INICIO;
	posicionar = false;
	bool cl = false;   //The cl- bools return true if a consoleClear() is launched
	bool clp = false;
	bool cld = false;
	bool clc = false;
	bool clf = false;
	pos_pantalla.px=0; //touchpad positions
	pos_pantalla.py=0;
	//Set the volume to 100/250 and loop it
	mmEffectVolume(MOD_DAZZLER2, 100);
	mmStart(MOD_DAZZLER2, MM_PLAY_LOOP);

	while(1) 
	{
		touchRead(&pos_pantalla);
		while(pos_pantalla.px!=0 || pos_pantalla.py!=0)
		{ 
			touchRead(&pos_pantalla);
			if(pos_pantalla.px==0 && pos_pantalla.py==0)
			{
				if(mmActive())
				{
					 mmPause();
				}
				else if(!mmActive())
				{
					mmResume();
				}
			}
		}
		
		if(posicionar == true)
		{ 
		//Set up the initial position of the sprites every time you press START in the menu
		documento_sprite.x = 0;
		documento_sprite.y = 0;
		soldado.x = 20;
		soldado.y = 0;
		}

		if(estado==INICIO && cl==false)
		{
			consoleClear();
			cl=true;
		}

		if(estado==INICIO && cl==true)
		{
			clp=false;
			printf("\x1b[01;00H Preparate para comenzar tu ");
			printf("\x1b[02;00H mision. Eres un soldado");
			printf("\x1b[03;00H de elite, un boina amarilla.");
			printf("\x1b[04;00H Tu mision es recoger el ");
			printf("\x1b[05;00H maximo numero de documentos");
			printf("\x1b[06;00H secretos en el area de");
			printf("\x1b[07;00H infiltracion.");
			printf("\x1b[09;00H Date prisa pues tu tiempo");
			printf("\x1b[10;00H es limitado");
			printf("\x1b[14;11H Suerte camarada.");
			MostrarINICIO();
		}

		if(estado==PRADO && clp==false)
		{
			consoleClear();
			clp=true;	
			posicionar = false;
		}

		if(estado==PRADO && clp==true)
		{
			cld=false;
			MostrarPRADO();
			printf("\x1b[02;05HDocumentos recogidos: %d", documentos);
			printf("\x1b[10;09H  Tiempo:%d", contador);
			//Show sprites and run sprite move function
			movimientoSoldado(&soldado);
			respawnDocumento(&documento_sprite);
		}

		if(estado==DESIERTO && cld==false)
		{
			consoleClear();
			cld=true;
		}

		if(estado==DESIERTO && cld==true)
		{
			clc=false;
			MostrarDESIERTO();
			printf("\x1b[02;05HDocumentos recogidos: %d", documentos);
			printf("\x1b[10;09H  Tiempo:%d", contador);
			//Show sprites and run sprite move function
			movimientoSoldado(&soldado);
			respawnDocumento(&documento_sprite);
		}

		if(estado==CARRETERA && clc==0)
		{
			consoleClear();
			clc=1;
		}

		if(estado==CARRETERA && clc==true)
		{
			clf=false;
			MostrarCARRETERA();
			printf("\x1b[02;05HDocumentos recogidos: %d", documentos);
			printf("\x1b[10;09H  Tiempo:%d", contador);
			//Show sprites and run sprite move function
			movimientoSoldado(&soldado);
			respawnDocumento(&documento_sprite);
		}

		if(estado==FINAL && clf==false)
		{
			consoleClear();
			clf=true;
		}

		if(estado==FINAL && clf==true)
		{
			soldado.x = 1000;
			documento_sprite.x = 3000;
			cl=false;
			MostrarNUBES();
			printf("\x1b[02;05HDocumentos recogidos: %d", documentos);
			//Show sprites and run sprite move function
			movimientoSoldado(&soldado);
			respawnDocumento(&documento_sprite);
		}
		
		if (collisionDetected(documento_sprite, soldado)) 
		{
			documentos++;
			// move the document to a random place but within the screen, dimensions to which I have subtracted the dimension
			//of the document so that it is not generated outside and you cannot collect it
			documento_sprite.x = rand() % (256-16) + 1; 
			documento_sprite.y = rand() % (192-16) + 1; 
		}

		//These functions are needed to update the sprites and the upper screen to be able to see them above the background.
		swiWaitForVBlank();
		oamUpdate(&oamMain);
	}
}
