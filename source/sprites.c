/*---------------------------------------------------------------------------------
Este código se ha implementado basándose en el ejemplo "Simple sprite demo" de 
dovoto y otro de Jaeden Amero
---------------------------------------------------------------------------------*/

#include <nds.h>			//library developed for the nds
#include <stdio.h>			//c standard library that defines the standard input and output functions
#include <stdlib.h>			//standard c library for memory reservation and number conversion
#include <unistd.h>			//library to ensure compatibility between operating systems
#include "sprites.h"
#include "defines.h"
#include "spritesheet.h"

u16* gfxRombo;
u16* gfxRomboGrande;


/* Initialize Sprite memory. */
void initSpriteMem() {

	//int i;
	oamInit(&oamMain, SpriteMapping_1D_32, false);
	oamInit(&oamSub, SpriteMapping_1D_32, false);

	gfxRombo =    oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxRomboGrande = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	
}



/* Within this function you have to define the color with which each of the 256 will be displayed
 * possible colors on the main screen. The 0 is transparent and the undefined are black.
 */
void establecerPaletaPrincipal() {
                                         // 0: TRANSPARENTE
   SPRITE_PALETTE[1]  = RGB15(31,0,0);   // ROJO:           RGB24={FF,00,00} los pixels con valor 1 aparecen en rojo
   SPRITE_PALETTE[2]  = RGB15(31,31,0);  // AMARILLO:       RGB24={FF,FF,00}
   SPRITE_PALETTE[3]  = RGB15(31,31,31); // BLANCO:         RGB24={FF,FF,FF}
   SPRITE_PALETTE[4]  = RGB15(0,31,0);   // VERDE:          RGB24={00,FF,00}
   SPRITE_PALETTE[5]  = RGB15(0,0,31);   // AZUL:           RGB24={00,00,FF}
   SPRITE_PALETTE[6]  = RGB15(0,0,0);    // NEGRO:          RGB24={00,00,00}
   SPRITE_PALETTE[7]  = RGB15(0,31,31);  // CYAN:           RGB24={00,FF,FF}
   SPRITE_PALETTE[8]  = RGB15(31,0,31);  // MAGENTA:        RGB24={FF,00,FF}
   SPRITE_PALETTE[9]  = RGB15(16,16,16); // GRIS:           RGB24={80,80,80}
   SPRITE_PALETTE[10] = RGB15(25,25,25); // GRIS CLARO:     RGB24={D0,D0,D0}
   SPRITE_PALETTE[11] = RGB15(8,8,8);    // GRIS OSCURO:    RGB24={40,40,40}
   SPRITE_PALETTE[12] = RGB15(31,19,0);  // NARANJA:        RGB24={FF,99,00}
   SPRITE_PALETTE[13] = RGB15(19,0,4);   // GRANATE:        RGB24={99,00,21}
   SPRITE_PALETTE[14] = RGB15(25,0,0);   // MARRON:         RGB24={66,00,00}
   SPRITE_PALETTE[15] = RGB15(16,0,16);  // MORADO:         RGB24={80,00,80}
   SPRITE_PALETTE[16] = RGB15(25,19,31); // LILA:           RGB24={CC,99,FF}
   SPRITE_PALETTE[17] = RGB15(31,19,25); // ROSA:           RGB24={FF,99,CC}
   SPRITE_PALETTE[18] = RGB15(23,21,21); // AZUL CLARO:     RGB24={BB,FF,FF}
   SPRITE_PALETTE[19] = RGB15(0,0,16);   // AZUL MARINO:    RGB24={00,00,80}
   SPRITE_PALETTE[20] = RGB15(0,16,16);  // VERDE AZULADO:  RGB24={00,80,80}
   SPRITE_PALETTE[21] = RGB15(0,12,0);   // VERDE OSCURO:   RGB24={00,66,00}
   SPRITE_PALETTE[22] = RGB15(16,16,0);  // VERDE OLIVA:    RGB24={80,80,00}
   SPRITE_PALETTE[23] = RGB15(19,31,19); // VERDE CLARO:    RGB24={99,FF,99}
   SPRITE_PALETTE[24] = RGB15(31,31,19); // AMARILLO CLARO: RGB24={FF,FF,99}
}


/* Drawn from a 16x16 pixel Sprite */

/* Due to the operation of memory banks, the first four rows
 * form the upper left quadrant, the following, the upper quadrant
 * right, the following the lower left quadrant and the last four
 * rows, the lower right quadrant, as shown to the side.
 */


u8 Rombo[256] = 
{
	0,0,0,0,0,0,5,5,0,0,0,0,0,5,5,5,	//	0,0,0,0,0,0,5,5, 5,5,0,0,0,0,0,0,
	0,0,0,0,5,5,5,5,0,0,0,5,5,5,5,5,	//	0,0,0,0,0,5,5,5, 5,5,5,0,0,0,0,0,
	0,0,5,5,5,5,5,5,0,5,5,5,5,5,5,5,	//	0,0,0,0,5,5,5,5, 5,5,5,5,0,0,0,0,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,	//	0,0,0,5,5,5,5,5, 5,5,5,5,5,0,0,0,
 
	5,5,0,0,0,0,0,0,5,5,5,0,0,0,0,0,	//	0,0,5,5,5,5,5,5, 5,5,5,5,5,5,0,0,
	5,5,5,5,0,0,0,0,5,5,5,5,5,0,0,0,	//	0,5,5,5,5,5,5,5, 5,5,5,5,5,5,5,0,
	5,5,5,5,5,5,0,0,5,5,5,5,5,5,5,0,	//	5,5,5,5,5,5,5,5, 5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,	//	5,5,5,5,5,5,5,5, 5,5,5,5,5,5,5,5,

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	//	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,	//	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,	//	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,	//	0,0,1,1,1,1,1,1, 1,1,1,1,1,1,0,0,

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	//	0,0,0,1,1,1,1,1, 1,1,1,1,1,0,0,0,
	1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,	//	0,0,0,0,1,1,1,1, 1,1,1,1,0,0,0,0,
	1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,	//	0,0,0,0,0,1,1,1, 1,1,1,0,0,0,0,0,
	1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,	//	0,0,0,0,0,0,1,1, 1,1,0,0,0,0,0,0,
};

/* Drawn of a 32x32 pixel Sprite */

u8 RomboGrande[1024] = 
{
	0,0,0,0,0,0,5,5,0,0,0,0,0,5,5,5,0,0,0,0,5,5,5,5,0,0,0,5,5,5,5,5,0,0,5,5,5,5,5,5,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,	

	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	

	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	
 
	5,5,0,0,0,0,0,0,5,5,5,0,0,0,0,0,5,5,5,5,0,0,0,0,5,5,5,5,5,0,0,0,5,5,5,5,5,5,0,0,5,5,5,5,5,5,5,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,	

	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,

	0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	

	1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	

	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,5,5,5,5,5,5,5,0,0,5,5,5,5,5,5,0,0,0,5,5,5,5,5,0,0,0,0,5,5,5,5,0,0,0,0,0,5,5,5,0,0,0,0,0,0,5,5,	

	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,5,5,5,5,5,5,0,0,5,5,5,5,5,0,0,0,5,5,5,5,0,0,0,0,5,5,5,0,0,0,0,0,5,5,0,0,0,0,0,0,	

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,	

	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	

	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,	
};

/* For each Sprite that you want to bring to the screen, you must do one of these functions. */

void BorrarRombo(int indice, int x, int y) {
oamSet(&oamMain, //main graphics engine context
	indice,  //oam index (0 to 127)  
	x, y,    //x and y pixle location of the sprite
	0,       //priority, lower renders last (on top)
	0,       //this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxRombo,//+16*16/2, 	//pointer to the loaded graphics
	-1,                  	//sprite rotation data  
	false,               	//double the size when rotating?
	true,			//hide the sprite?
	false, false, 		//vflip, hflip
	false			//apply mosaic
	); 
oamUpdate(&oamMain); 
}

void MostrarRombo (int indice, int x, int y){ 
oamSet(&oamMain, //main graphics engine context
	indice,  //oam index (0 to 127)  
	x, y,    //x and y pixle location of the sprite
	0,       //priority, lower renders last (on top)
	0,       //this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxRombo,//+16*16/2, 	//pointer to the loaded graphics
	-1,                  	//sprite rotation data  
	false,               	//double the size when rotating?
	false,			//hide the sprite?
	false, false, 		//vflip, hflip
	false			//apply mosaic
	); 
oamUpdate(&oamMain);  
}

void BorrarRomboGrande(int x, int y){
oamSet(&oamMain, //main graphics engine context
	127,     //oam index (0 to 127)  
	x, y,    //x and y pixle location of the sprite
	0,       //priority, lower renders last (on top)
	0,       //this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxRomboGrande,//+16*16/2,	//pointer to the loaded graphics
	-1,                  	//sprite rotation data  
	false,               	//double the size when rotating?
	true,			//hide the sprite?
	false, false, 		//vflip, hflip
	false			//apply mosaic
	); 
oamUpdate(&oamMain); 
}

void MostrarRomboGrande (int x, int y){
oamSet(&oamMain, //main graphics engine context
	127,     //oam index (0 to 127)  
	x, y,    //x and y pixle location of the sprite
	0,       //priority, lower renders last (on top)
	0,       //this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxRomboGrande,//+16*16/2,	//pointer to the loaded graphics
	-1,                  	//sprite rotation data  
	false,               	//double the size when rotating?
	false,			//hide the sprite?
	false, false, 		//vflip, hflip
	false			//apply mosaic
	); 
oamUpdate(&oamMain);  
}


void guardarSpritesEnMemoria(){ //Save sprites in memory
	
int i;
	//for 16 * 16 sprites
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxRombo[i] = Rombo[i*2] | (Rombo[(i*2)+1]<<8);				
	}
	//for 32 * 32 sprites
	for(i = 0; i < 32 * 32 / 2; i++) 
	{	
		gfxRomboGrande[i] = RomboGrande[i*2] | (RomboGrande[(i*2)+1]<<8);				
	}
}


