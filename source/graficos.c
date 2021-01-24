#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Define the video system */
void initVideo() 
{
        /*  Map VRAM memory to display graphics on both screens. */
    
    vramSetMainBanks(VRAM_A_MAIN_BG_0x06000000,
                    VRAM_B_MAIN_BG_0x06020000,
                    VRAM_C_SUB_BG_0x06200000,
                    VRAM_E_LCD);

    vramSetBankE(VRAM_E_MAIN_SPRITE);
    vramSetBankD(VRAM_D_SUB_SPRITE);

        /*  Set the video mode of the main screen. */
    videoSetMode(MODE_5_2D | // Establecer el modo gráfico 5
                DISPLAY_BG2_ACTIVE | // Activar el fondo 2
                DISPLAY_BG3_ACTIVE); // Activar el fondo 3

    /*  Set the video mode of the secondary display. */
    videoSetModeSub(MODE_5_2D | // Establecer el modo gráfico 5
                    DISPLAY_BG3_ACTIVE); // Activar el fondo 3
}
