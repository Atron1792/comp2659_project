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
#include "music.h"
#include "input.h"


/* SPLASH SCREEN CONSTANTS */
#define BORDER_THICK 2
#define BORDER_WIDTH 72
#define BORDER_LENGTH 16

#define P1_OPT_X 196
#define P1_OPT_Y 288

#define P2_OPT_X 220
#define P2_OPT_Y 288

/* Game and framebuffer constants */
#define ESC_KEY '\x1b'
#define FRAMEBUFFER_SIZE 32000
#define FRAMEBUFFER_ALIGNMENT 256

/*----- Function: getTime -----

 PURPOSE: Reads the TOS system timer without leaving supervisor mode active.

 INPUT: None

 OUTPUT: UINT32 - Current value of the TOS 70 Hz vertical blank counter.

 ASSUMPTIONS: The caller permits a brief transition between supervisor and user mode.
*/
UINT32 getTime();

/*----- Function: initDoubleBuffer -----

 PURPOSE: Saves the original screen and prepares an aligned off-screen buffer.

 INPUT: model(GameMdl *) - Game model whose drawing framebuffer is set to the aligned back buffer.

 OUTPUT: None

 ASSUMPTIONS: model points to writable, initialized game state.
*/
void initDoubleBuffer(GameMdl* model);

/*----- Function: presentFrame -----

 PURPOSE: Displays the completed back buffer and selects the old front buffer
          for the next frame.

 INPUT: model(GameMdl *) - Game model whose drawing framebuffer is updated.

 OUTPUT: None

 ASSUMPTIONS: initDoubleBuffer() has been called before this function.
*/
void presentFrame(GameMdl* model);

/*----- Function: restoreScreen -----

 PURPOSE: Restores the framebuffer that was active before double buffering.

 INPUT: None

 OUTPUT: None

 ASSUMPTIONS: The original screen address is available from the initDoubleBuffer() call.
*/
void restoreScreen();

/*----- Function: processInput -----

 PURPOSE: Processes one pending keyboard request for the game.

 INPUT: model(GameMdl *) - Game model whose jump or quit state may be updated.

 OUTPUT: None

 ASSUMPTIONS: model points to writable game state.
*/
void processInput(GameMdl *model);

/*----- Function: updateGame -----

 PURPOSE: Applies a clock-triggered gameplay update and presents the frame
          when the update interval has elapsed.

 INPUT: model(GameMdl *) - Game model to update and render.

 OUTPUT: None

 ASSUMPTIONS: initDoubleBuffer() and gameInit() have initialized timing and framebuffer state.
*/
void updateGame(GameMdl *model);

/*----- Function: updateGame -----

 PURPOSE: Applies a clock-triggered gameplay update and presents the frame
          when the update interval has elapsed.

 INPUT: model(GameMdl *) - Game model to update and render.

 OUTPUT: int - returns 1 for 1-player, and 2 for 2-player

 ASSUMPTIONS: 
*/
int gameSplashScreen(GameMdl* model);

/*----- Function: renderEndScreen -----

 PURPOSE: Draws the terminal message and final game objects for the current
          game status.

 INPUT: model(GameMdl *) - Game model containing the terminal status and object state.

 OUTPUT: None

 ASSUMPTIONS: model points to valid, initialized game state.
*/
void renderEndScreen(GameMdl *model);

/*----- Function: gameInit -----

 PURPOSE: Initializes game state and the game-loop clock values.

 INPUT: model(GameMdl *) - Game model to initialize.

 OUTPUT: None

 ASSUMPTIONS: model's sprite pointers have already been assigned.
*/
void gameInit(GameMdl* model);

/*----- Function: gameLoop -----

 PURPOSE: Runs input polling, timed updates, rendering, and terminal screens.

 INPUT: model(GameMdl *) - Initialized game model used by the loop.

 OUTPUT: None

 ASSUMPTIONS: The model and its sprite pointers are valid.
*/
void gameLoop(GameMdl* model);

#endif