/*
File Name: cond.h
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Declares collision detection and game-status condition handlers.
*/

#ifndef COND_H
#define COND_H

#include "model.h"
#include "bitmaps.h"
#include "effects.h"

/*Dino and Cactus Hitbox constants

The numbers are set this way to provide a more balancing hitbox for the player.

*/
#define DINO_HITBOX_WIDTH 24
#define DINO_HITBOX_HEIGHT 26
#define CACTUS_HITBOX_WIDTH 28
#define CACTUS_HITBOX_HEIGHT 32


/*----- Function: checkCollision -----

 PURPOSE: Detects whether the dinosaur and cactus overlap.

 INPUT: model(const GameMdl *) - Read-only game model containing both sprites.

 OUTPUT: signed int - Nonzero when the sprites overlap; zero otherwise.

 ASSUMPTIONS: Null sprite pointers are treated as no collision.
*/
signed int checkCollision(const GameMdl *model);

/*----- Function: onCollision -----

 PURPOSE: Records a dinosaur-cactus collision as a loss.

 INPUT: model(GameMdl *) - Writable game model whose status is updated.

 OUTPUT: None

 ASSUMPTIONS: model points to writable game state.
*/
void onCollision(GameMdl *model);

/*----- Function: onQuit -----

 PURPOSE: Records a quit condition in the game status.

 INPUT: model(GameMdl *) - Writable game model whose status is updated.

 OUTPUT: None

 ASSUMPTIONS: model points to writable game state.
*/
void onQuit(GameMdl* model);

#endif