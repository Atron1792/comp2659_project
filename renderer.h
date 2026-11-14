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

 INPUT: model - read-only game state and framebuffer to render.

 OUTPUT: None.
*/
void render(const GameMdl *model);

/*----- Function: renderGround -----

 PURPOSE: Draws the horizontal ground line.

 INPUT: base - framebuffer address.

 OUTPUT: None.
*/
void renderGround(UINT32 *base);

/*----- Function: renderDino -----

 PURPOSE: Draws the dinosaur animation frame selected by vertical velocity.

 INPUT: dino - dinosaur state; base - framebuffer address.

 OUTPUT: None.
*/
void renderDino(const Dino *dino, UINT32 *base);

/*----- Function: renderCactus -----

 PURPOSE: Draws the complete cactus bitmap.

 INPUT: cactus - cactus state; base - framebuffer address.

 OUTPUT: None.
*/
void renderCactus(const Cactus *cactus, UINT32 *base);

/*----- Function: renderScore -----

 PURPOSE: Draws the current score as five digits in the top-right corner.

 INPUT: score - numeric score; base - framebuffer address.

 OUTPUT: None.
*/
void renderScore(UINT32 score, UINT32* base);

/*----- Function: disableCursor -----

 PURPOSE: Hides the terminal cursor while the game is running.

 INPUT: None.

 OUTPUT: None.
*/
void disableCursor();
#endif