/*
file name: asynch.h
authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Declares handlers for asynchronous user requests.
*/

#ifndef ASYNCH_H
#define ASYNCH_H

#include "model.h"

/*----- Function: onJumpRequest -----

 PURPOSE: Starts a dinosaur jump when the dinosaur is standing on the floor.

 INPUT: model - game model containing the dinosaur to update.

 OUTPUT: None.

 ASSUMPTIONS: model and its dinosaur pointer are valid.
*/
void onJumpRequest(GameMdl *model);

/*----- Function: onQuitRequest -----

 PURPOSE: Sets the quit status flag in the game model.

 INPUT: model - game model whose status is updated.

 OUTPUT: None.

 ASSUMPTIONS: model points to writable game state.
*/
void onQuitRequest(GameMdl *model);

#endif