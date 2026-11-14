/*
File Name: synch.h
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Declares synchronous clock-tick processing for game state updates.
*/

#ifndef SYNCH_H
#define SYNCH_H

#include "model.h"

/*----- Function: onClockTick -----

 PURPOSE: Advances timed game state and applies collision handling.

 INPUT: model - writable game model to update.

 OUTPUT: Nonzero when a collision is detected; zero otherwise.
*/
signed int onClockTick(GameMdl *model);

#endif