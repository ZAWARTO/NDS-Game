# Description

 This game made it with [devkitPro](https://devkitpro.org/wiki/Getting_Started) is a good tutorial of low code key scanner handlers, 
 timers, touch screen read handler, sprites and background management, use of the VRAM, masks of the
 interruption and initial directions of care routines
 and use of music with [maxmod9](https://maxmod.devkitpro.org/). The emulator used to test it is [No$GBA](https://www.nogba.com/). The sprite management is based on the example [basic-first-game](https://github.com/jdriselvato/NDS-Development/tree/master/examples/Graphics/basic-first-game) of [jdriselvato](https://github.com/jdriselvato).

## Game 

The objective of the game is for the yellow beret to collect as many documents as possible,
it's the same document but every time you pick it up a point is added and it appears randomly
in another side. To do this, the yellow beret can be moved to the right, left, up
or down on the screen. In other words, the main objective of the project is to go
moving the soldier to the right, left, up or down with the keys
right arrow, left arrow, up arrow or down arrow, respectively.

For each document collected by the soldier, the player will get a point and another will appear
again in a random position of the screen.
While playing, the player will be informed on the upper screen of the time it has taken
in the current scenario as well as the number of points obtained. A document is considered collected
when the soldier is placed in such position that its dimensions collide with those of the
document, the dimensions of both the document and the soldier are 16x16 pixels.

The game ends when the stipulated time has passed (15 segs) in each scenario and and you go through 
all three scenarios which will take you to the NUBES screen whose state is called final.
Once the game is over, the number of documents collected must be shown on the upper screen. 
In addition, a message will be displayed asking the user to press the
SELECT key to return to the menu that is the title screen.

The following keys will be used:

 - Right arrow ----> Move the soldier to the right.
 - Left arrow ------> Move the soldier to the left.
 - Up arrow -------> Move the soldier up.
 - Down arrow ----> Move the soldier down.
 - START key: -----> To start a new game when you are on the title screen.
 - SELECT key: ----> To return to the title screen from the final screen.

## Mechanism

What is most striking is the data structures that I used at the beginning,
its function is to use gfx and gfx_frame to name 16 and 8 bit unasigned ints and
x and y positions of each sprite, for this reason then when starting the sprites we have done it in the
main and not in sprites.c. This is useful since spritesheet.png are actually 5 sprites and according to each
movement status a soldier sprite is displayed and for the document the last one is displayed
slice (png partition) of dimensions 16x16 pixels corresponding to the dimension of each
sprite, 5 16x16 blocks in a 16x80 png. In this way it was easier to implement the
sprites and I have build it as tiles to make the partition.

The scanning of the right arrow, down arrow, left arrow, arrow keys
up as well as the touch screen, will be done by survey. The START and
SELECT will be synchronized by interruption. The rest of the keys, in principle, are not used.

The movementSoldier(Soldier  soldier) which is void whose parameter is the soldier defined in the
data structure, the movement keys go by survey and define the change of position
the soldier sprite and a state defined in defines.h so that the sprite changes according to
where you move to simulate movement rotation. 

There are a total of five bool variables prefixed with cl-, these determine if a console cleanup has already been performed
to write new text on the top screen, each state changes the cleaning boolean
from the following state to false so that with the conditional in the following state it performs a
text cleanup and then each state changes its variable to true so it doesn't repeat cleaning
continuously and passes to another conditional. 

In the conditional of randomly changing thedocument position is subtracted from the range of random numbers between 0 and 256 and 0
and 192 which are the maximum x and y positions of the screen, the subtraction is 16 pixels and this avoids
the document to appear off the screen. The other most notable part of the project is the
music implementation, we have made it in .mod format since the maxmod9.h library
which comes by default can only play that format, .xl and some more so we have
modified the makefile so that it can create soundbank_bin.h and save soundbank.h in
memory use .mod files from the audio folder and is able to play them, playback at startup
its automatic and you can pause and resume it by pressing the touch screen regardless of the
game state.

## Structure
- Makefile ----> File to compile.
- audio -------> Song of the game in .mod file
- gfx ----------> Directory that contains the figures for the background and the sprites.
- include -----> Directory that contains the header files.

  - define.h 
    - In this file the necessary definitions are added to be able to use more significant names (states, keys,etc).		 
  - rutservs.h  
    - Extern voids of interruptions.
  - fondos.h 
    - Procedure to initialize the backgrounds and extern voids of the backgrounds print function.
  - sprites.h 
    - Initialize the sprite memory, colors and save it into memory.
  - teclado.h 
    - Variable to store the value of the key pressed and extern int TeclaPulsada().
  - temporizadores.h 
    - Extern void IntTemp() (automatically called by the interrupt manager).

- source	-------> Directory that contains the files with the source code.

  - fondos.c 
    - Routines for managing backgrounds.
  - sprites.c 
    - Routines for handling sprites (save it into memory, palettes, etc).
  - graficos.c 
    - Routines for graphics management.
  - main.c
    - Main program.
  - rutserv.c 
    - The interrupts routines to program the controls and initialize the table of interrupts in this file.	
  - teclado.c 
    - Those routines related to keys control are included here.
  - temporizadores.c 
    - Those routines related to the timer control are included here.
    
## State Machine
![State Machine Diagram](https://github.com/ZAWARTO/NDS-Game/blob/master/State%20Machine%20Diagram.jpeg)


## License
[MIT](https://choosealicense.com/licenses/mit/)
