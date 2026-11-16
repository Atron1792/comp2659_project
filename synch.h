/*
File Name: synch.h
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Declares synchronous clock-tick processing for game state updates.
*/

#ifndef SYNCH_H
#define SYNCH_H

#include "model.h"

/*----- Function: onClockTick -----

 PURPOSE: Advances dinosaur and cactus movement and updates the score.

 INPUT: model - writable game model to update.

 OUTPUT: None.

 ASSUMPTIONS: One call represents one 70 Hz game tick. The score increases
              once every seven calls.
*/
void onClockTick(GameMdl *model);

#endif