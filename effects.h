/*
File Name: effects.h
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Declares gameplay sound effects layered on top of the PSG module.
*/

#ifndef EFFECTS_H
#define EFFECTS_H

/* Jump sound effect */
#define JUMP_TONE_PERIOD 0x0090
#define JUMP_ENVELOPE_PERIOD 0x0310

/* Collision sound effect */
#define COLLISION_NOISE_PERIOD 0x001F
#define COLLISION_ENVELOPE_PERIOD 0x0310

/* Enables envelope-controlled volume */
#define ENVELOPE_VOLUME 0x10

/*----- Function: playJumpEffect -----

 PURPOSE: Starts the jump sound effect.

 OUTPUT: None.

 ASSUMPTIONS: The PSG is available for sound effects on channel C.
*/
void playJumpEffect();

/*----- Function: playCollisionEffect -----

 PURPOSE: Starts the collision sound effect.

 OUTPUT: None.

 ASSUMPTIONS: The PSG is available for sound effects on channel C.
*/
void playCollisionEffect();

#endif