/*
File Name: music.h
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Declares the music playback interface layered on top of the PSG module.
*/

#ifndef MUSIC_H
#define MUSIC_H

#include "TYPES.H"
#include "psg.h"

#define MUSIC_VOLUME 3
#define MUSIC_NOTE_COUNT 16

typedef struct {
    UINT16 tuning;
    UINT32 duration;
} MusicNote;

/*----- Function: startMusic -----

 PURPOSE: Starts playback of the game's looping background music.

 INPUT: None

 OUTPUT: None

 ASSUMPTIONS: The PSG is available for music playback on channel A.
*/
void startMusic();

/*----- Function: stopMusic -----

 PURPOSE: Stops background music and silences all PSG sound.

 INPUT: None

 OUTPUT: None

 ASSUMPTIONS: Channel A is used only for background music.
*/
void stopMusic();

/*----- Function: updateMusic -----

 PURPOSE: Advances the current music note when enough time has elapsed.

 INPUT: timeElapsed(UINT32) - Vertical-blank ticks elapsed since the previous call.

 OUTPUT: None

 ASSUMPTIONS: startMusic() has been called before this function.
*/
void updateMusic(UINT32 timeElapsed);

#endif