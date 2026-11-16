/*
File Name: game.h
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Declares game initialization, timing, screen setup, and main-loop routines.
*/

#ifndef GAME_H
#define GAME_H

/* Includes */
#include <osbind.h>
#include <stdio.h>
#include <stdlib.h>

#include "TYPES.H"
#include "raster.h"
#include "renderer.h"
#include "model.h"
#include "asynch.h"
#include "synch.h"
#include "cond.h"

/*----- Function: getTime -----

 PURPOSE: Reads the TOS system timer without leaving supervisor mode active.

 INPUT: None.

 OUTPUT: The current timer value.
*/
UINT32 getTime();

/*----- Function: initDoubleBuffer -----

 PURPOSE: Saves the original screen and prepares an aligned off-screen buffer.

 INPUT: model - game model whose drawing framebuffer is set to the back buffer.

 OUTPUT: None.
*/
void initDoubleBuffer(GameMdl* model);

/*----- Function: presentFrame -----

 PURPOSE: Displays the completed back buffer and selects the old front buffer
          for the next frame.

 INPUT: model - game model whose drawing framebuffer is updated.

 OUTPUT: None.

 ASSUMPTIONS: initDoubleBuffer() has been called before this function.
*/
void presentFrame(GameMdl* model);

/*----- Function: restoreScreen -----

 PURPOSE: Restores the framebuffer that was active before double buffering.

 INPUT: None.

 OUTPUT: None.
*/
void restoreScreen(void);

/*----- Function: gameInit -----

 PURPOSE: Initializes game state and the game-loop clock values.

 INPUT: model - game model to initialize.

 OUTPUT: None.
*/
void gameInit(GameMdl* model);

/*----- Function: gameLoop -----

 PURPOSE: Runs input polling, timed updates, rendering, and terminal screens.

 INPUT: model - initialized game model used by the loop.

 OUTPUT: None.

 ASSUMPTIONS: The model and its sprite pointers are valid.
*/
void gameLoop(GameMdl* model);

#endif