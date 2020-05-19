extern u16* gfxBola;
extern u16* gfxRaqueta;

/* Initialize Sprite memory. */
extern void initSpriteMem();

/* Within this function you have to define the color with which each of the 256 will be displayed
 * possible colors on the main screen. The 0 is transparent and the undefined are black.
 */
extern void establecerPaletaPrincipal();

/* Within this function you have to define the color with which each of the 256 will be displayed
 * possible colors on the secondary display. The 0 is transparent and the undefined are black.
 */
extern void establecerPaletaSecundaria();

/* To save the sprites in memory and then be able to use them. */

extern void guardarSpritesEnMemoria();

/* Specific functions to manage sprites. */

extern void MostrarRombo(int indice, int x, int y);
extern void BorrarRombo(int indice, int x, int y);

extern void MostrarRomboGrande(int x, int y);
extern void BorrarRomboGrande(int x, int y);







