/*
File Name: cond.h
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Declares collision detection and game-status condition handlers.
*/

#ifndef COND_H
#define COND_H

#include "model.h"

/*Dino and Cactus Hitbox constants

The numbers are set this way to provide a more balancing hitbox for the player.

*/
#define DINO_HITBOX_WIDTH 24
#define DINO_HITBOX_HEIGHT 26
#define CACTUS_HITBOX_WIDTH 28
#define CACTUS_HITBOX_HEIGHT 32


/*----- Function: checkCollision -----

 PURPOSE: Detects whether the dinosaur and cactus overlap.

 INPUT: model - read-only game model containing both sprites.

 OUTPUT: Returns nonzero when the sprites overlap, otherwise zero.

 ASSUMPTIONS: Null sprite pointers are treated as no collision.
*/
signed int checkCollision(const GameMdl *model);

/*----- Function: onCollision -----

 PURPOSE: Records a dinosaur-cactus collision as a loss.

 INPUT: model - writable game model whose status is updated.

 OUTPUT: None.
*/
void onCollision(GameMdl *model);

/*----- Function: onQuit -----

 PURPOSE: Records a quit condition in the game status.

 INPUT: model - writable game model whose status is updated.

 OUTPUT: None.
*/
void onQuit(GameMdl* model);

#endif