/*
File Name: renderer.h
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Declares scene and sprite rendering routines for the game framebuffer.
*/

#ifndef RENDERER_H
#define RENDERER_H

#include "model.h"
#include "TYPES.H"
#include "raster.h"
#include "bitmaps.h"

#define MENU_BUTTON_ROW 160
#define MENU_BUTTON_COL 220
#define MENU_BUTTON_HEIGHT 42
#define MENU_BUTTON_WIDTH 200
#define MENU_BUTTON_GAP 16
#define MENU_BORDER_THICK 2

/*----- Function: renderGame -----

 PURPOSE: Draws the complete current game scene.

 INPUT: model(const GameMdl *) - Read-only game state and framebuffer to render.

 OUTPUT: None

 ASSUMPTIONS: model's dinosaur and cactus pointers are valid.
*/
void renderGame(const GameMdl *model);

/*----- Function: renderMenuButton -----

 PURPOSE: Draws a rectangular menu button and highlights it when selected.

 INPUT: base(UINT32 *) - Framebuffer address.
        row(int) - Top row of the button.
        label(char *) - Text displayed in the button.
        labelCol(int) - Column where the label begins.
        selected(int) - Nonzero to draw the selection border.

 OUTPUT: None

 ASSUMPTIONS: base points to a valid monochrome framebuffer.
*/
void renderMenuButton(UINT32 *base, int row, char *label, int labelCol, int selected);

/*----- Function: renderSplashScreen -----

 PURPOSE: Draws the main menu and highlights the selected option.

 INPUT: base(UINT32 *) - Framebuffer address.
        selectedOption(int) - Zero-based index of the selected menu button.

 OUTPUT: None

 ASSUMPTIONS: base points to a valid monochrome framebuffer.
*/
void renderSplashScreen(UINT32 *base, int selectedOption);

/*----- Function: renderGround -----

 PURPOSE: Draws the horizontal ground line.

 INPUT: base(UINT32 *) - Framebuffer address.

 OUTPUT: None

 ASSUMPTIONS: base points to a valid monochrome framebuffer.
*/
void renderGround(UINT32 *base);

/*----- Function: renderDino -----

 PURPOSE: Draws the dinosaur animation frame selected by vertical velocity.

 INPUT: dino(const Dino *) - Dinosaur state.
        base(UINT32 *) - Framebuffer address.

 OUTPUT: None

 ASSUMPTIONS: dino and base point to valid state and framebuffer memory.
*/
void renderDino(const Dino *dino, UINT32 *base);

/*----- Function: renderCactus -----

 PURPOSE: Draws the complete cactus bitmap. In the case of multiple cacti, draws them in a row with a fixed separation.

 INPUT: cactus(const Cactus *) - Cactus state.
        base(UINT32 *) - Framebuffer address.

 OUTPUT: None

 ASSUMPTIONS: base points to a valid monochrome framebuffer.
*/
void renderCactus(const Cactus *cactus, UINT32 *base);

/*----- Function: renderScore -----

 PURPOSE: Draws the current score as five digits in the top-right corner.

 INPUT: score(UINT32) - Numeric score.
        base(UINT32 *) - Framebuffer address.

 OUTPUT: None

 ASSUMPTIONS: The score is formatted into a five-digit string.
*/
void renderScore(UINT32 score, UINT32* base);

/*----- Function: disableCursor -----

 PURPOSE: Hides the terminal cursor while the game is running.

 INPUT: None

 OUTPUT: None

 ASSUMPTIONS: The function is called from a TOS text console.
*/
void disableCursor();
#endif