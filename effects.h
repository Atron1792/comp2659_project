/*
File Name: effects.h
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Declares gameplay sound effects layered on top of the PSG module.
*/

#ifndef EFFECTS_H
#define EFFECTS_H

#include "TYPES.H"

/*----- Function: playJumpEffect -----

 PURPOSE: Starts the jump sound effect.

 OUTPUT: None.

 ASSUMPTIONS: The PSG is available for sound effects on channel C.
*/
void playJumpEffect(void);

/*----- Function: playCollisionEffect -----

 PURPOSE: Starts the collision sound effect.

 OUTPUT: None.

 ASSUMPTIONS: The PSG is available for sound effects on channel C.
*/
void playCollisionEffect(void);

#endif