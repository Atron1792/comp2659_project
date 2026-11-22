/*
File Name: music.h
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Declares the music playback interface layered on top of the PSG module.
*/

#ifndef MUSIC_H
#define MUSIC_H

#include "TYPES.H"

/*----- Function: startMusic -----

 PURPOSE: Starts playback of the game's looping background music.

 INPUT: None.

 OUTPUT: None.

 ASSUMPTIONS: The PSG is available for music playback on channel A.
*/
void startMusic(void);

/*----- Function: updateMusic -----

 PURPOSE: Advances the current music note when enough time has elapsed.

 INPUT: timeElapsed - number of vertical-blank ticks since the last update.

 OUTPUT: None.

 ASSUMPTIONS: startMusic() has been called before this function.
*/
void updateMusic(UINT32 timeElapsed);

#endif