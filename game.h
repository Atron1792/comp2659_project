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


/* Game and framebuffer constants */
#define ESC_KEY '\x1b'
#define FRAMEBUFFER_SIZE 32000
#define FRAMEBUFFER_ALIGNMENT 256

#define MENU_OPTION_COUNT 3

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

/*----- Function: gameSplashScreen -----

 PURPOSE: Displays the main menu. Tab changes the selected option, Enter
          activates 1 Player or Quit, and Esc exits. 2 Player is shown as
          coming soon and is not activated.

 INPUT: model(GameMdl *) - Game model whose framebuffer is used for the menu.

 OUTPUT: int - 1 to start a single-player game, or 0 to quit.

 ASSUMPTIONS: Double buffering has been initialized for model.
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

 ASSUMPTIONS: model's sprite pointers have already been assigned and initDoubleBuffer() has been called.
*/
void gameInit(GameMdl* model);

/*----- Function: gameLoop -----

 PURPOSE: Initializes gameplay, then runs input polling, timed updates, rendering, and terminal screens.

 INPUT: model(GameMdl *) - Game model whose sprite pointers are assigned.

 OUTPUT: None

 ASSUMPTIONS: The model's sprite pointers are assigned and double buffering has been initialized.
*/
void gameLoop(GameMdl* model);

#endif