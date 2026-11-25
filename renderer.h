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

/*----- Function: render -----

 PURPOSE: Draws the complete current game scene.

 INPUT: model(const GameMdl *) - Read-only game state and framebuffer to render.

 OUTPUT: None

 ASSUMPTIONS: model's dinosaur and cactus pointers are valid.
*/
void render(const GameMdl *model);

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