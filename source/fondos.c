
#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fondos.h"

/* add here includes for each background. */

#include "PRADO.h"
#include "INICIO.h"
#include "NUBES.h"
#include "CARRETERA.h"
#include "DESIERTO.h"


/* Select a DMA channel to copy images to memory */
static const int DMA_CHANNEL = 3;

/* Procedure to configure the background system. */
void initFondos() {
    /*  Set the background 3 affinity of the main screen with 16-bit color. */
    REG_BG3CNT = BG_BMP16_256x256 |
                 BG_BMP_BASE(0) | // The initial memory address
                 BG_PRIORITY(3); // Low priority

    /*  Set the transformation matrix to the bottom of main screen 3
        to the identity matrix. */
    REG_BG3PA = 1 << 8;
    REG_BG3PB = 0;
    REG_BG3PC = 0;
    REG_BG3PD = 1 << 8;

/*******************************************************************************************/
    /*  Define the situation of bottom 3 of the main screen. */
    /*  This should change according to the position in which you want to put the graph */
    REG_BG3X = 0;
    REG_BG3Y = 0;
/*******************************************************************************************/

    /*  Set the background 2 affinity of the main screen with 16-bit color. */
    REG_BG2CNT = BG_BMP16_128x128 |
                 BG_BMP_BASE(8) | // The initial memory address
                 BG_PRIORITY(2);  // Low priority


    /*  Set the transformation matrix to the bottom of main screen 2
        to the identity matrix. */
    REG_BG2PA = 1 << 8;
    REG_BG2PB = 0;
    REG_BG2PC = 0;
    REG_BG2PD = 1 << 8;

/*******************************************************************************************/
    /*  Define the situation of background 2 of the main screen. */
    /*  This should change according to the position in which you want to put the graph */
    REG_BG2X = -(SCREEN_WIDTH / 2 - 32) << 8;
    REG_BG2Y = -32 << 8;
/*******************************************************************************************/

    /*  Set the background 3 affinity of the secondary display with 16-bit color. */
    REG_BG3CNT_SUB = BG_BMP16_256x256 |
                     BG_BMP_BASE(0) | // The initial memory address
                     BG_PRIORITY(3); // Low priority

    /*  Set the transformation matrix in relation to background 3 of the secondary screen
        to the identity matrix. */
    REG_BG3PA_SUB = 1 << 8;
    REG_BG3PB_SUB = 0;
    REG_BG3PC_SUB = 0;
    REG_BG3PD_SUB = 1 << 8;

/*******************************************************************************************/
    /*  Define the background situation 3 of the secondary screen. */
    /*  This should change according to the position in which you want to put the graph */
    REG_BG3X_SUB = 0;
    REG_BG3Y_SUB = 0;
/*******************************************************************************************/
}

/* For each image that you want to bring to the screen, you must do one of these functions. */

void MostrarPRADO() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     PRADOBitmap, /* Automatically generated variable */
                     (uint16 *)BG_BMP_RAM(0), /* Main Fund 3 Address */
                     PRADOBitmapLen); /* Automatically generated length (in bytes) */
}

void MostrarINICIO() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     INICIOBitmap, /* Automatically generated variable */
                     (uint16 *)BG_BMP_RAM(0), /* Main Fund 3 Address */
                     INICIOBitmapLen); /* Automatically generated length (in bytes) */
}


void MostrarNUBES() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     NUBESBitmap, /* Automatically generated variable */
                     (uint16 *)BG_BMP_RAM(0), /* Main Fund 3 Address */
                     NUBESBitmapLen); /* Automatically generated length (in bytes) */
}

void MostrarDESIERTO() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     DESIERTOBitmap, /* Automatically generated variable */
                     (uint16 *)BG_BMP_RAM(0), /* Main Fund 3 Address */
                     DESIERTOBitmapLen); /* Automatically generated length (in bytes) */
}

void MostrarCARRETERA() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     CARRETERABitmap, /* Automatically generated variable */
                     (uint16 *)BG_BMP_RAM(0), /* Main Fund 3 Address */
                     CARRETERABitmapLen); /* Automatically generated length (in bytes) */
}

