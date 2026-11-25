/*
File Name: tst_mus.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Demonstrates usage of the music playback module.
*/
#include <osbind.h>
#include <stdio.h>
#include <stdlib.h>

#include "music.h"
#include "psg.h"
#include "TYPES.H"

static const MusicNote backgroundBeat[MUSIC_NOTE_COUNT] = {
    {268, 9}, {358, 3}, {268, 6}, {358, 6},
    {179, 3}, {536, 9}, {358, 6}, {451, 6},
    {358, 6}, {402, 6}, {451, 6}, {268, 6},
    {179, 3}, {358, 9}, {402, 6}, {451, 6}
};

volatile UINT32 *timer = (UINT32 *)0x462;
static UINT32 timeThen, timeNow;

/*----- Function: getTime -----

 PURPOSE: Pulled from game.c, reads the TOS system timer without leaving supervisor mode active.
  
 INPUT: None

 OUTPUT: UINT32 - Current value of the TOS 70 Hz vertical blank counter.

 ASSUMPTIONS: Supervisor mode is briefly enabled while the timer is read.
*/
UINT32 getTime() {
	UINT32 old_ssp, time;
	old_ssp = Super(0);
	time = *timer;
	Super(old_ssp);
	return time;
}

/*----- Function: tstStartMusic -----

 PURPOSE: Exercises starting background music playback.

 INPUT: None

 OUTPUT: None

 ASSUMPTIONS: startMusic() has initialized Channel A.
*/
static void tstStartMusic()
{
	UINT8 fine;
	UINT8 coarse;
	UINT8 volume;
	UINT8 mixer;
	UINT16 actualTuning;

	startMusic();
	readPsg(A_fine, &fine);
	readPsg(A_coarse, &coarse);
	readPsg(A_vol, &volume);
	readPsg(MIXER_IO, &mixer);
	actualTuning = ((UINT16)coarse << 8) | fine;

	printf("start music: expected = %u, actual = %u, volume = %u, mixer = %u\n", backgroundBeat[0].tuning, actualTuning, volume, mixer);
}

/*----- Function: tstUpdateMusic -----

 PURPOSE: Exercises advancing background music using elapsed time.

 INPUT: None

 OUTPUT: None

 ASSUMPTIONS: A key press ends the elapsed-time playback demonstration.
*/
static void tstUpdateMusic()
{
	UINT32 elapsed;

	timeThen = getTime();
	while (!Cconis()) {
		timeNow = getTime();
		elapsed = timeNow - timeThen;

		if (elapsed >= 1) {
			updateMusic(elapsed);
			timeThen = timeNow;
		}
	}
	Cconin();
}

/*----- Function: tstStopMusic -----

 PURPOSE: Exercises stopping playback through the music module.

 INPUT: None

 OUTPUT: None

 ASSUMPTIONS: stopMusic() has stopped background playback.
*/
static void tstStopMusic()
{
	UINT8 volume;

	stopMusic();
	readPsg(A_vol, &volume);
	printf("stop music: channel A volume = %u\n", volume);
}

/*----- Function: main -----

 PURPOSE: Runs the music-module test cases.

 INPUT: None

 OUTPUT: int - Zero after the test cases complete.
*/
int main()
{
	tstStartMusic();
	tstUpdateMusic();
	tstStopMusic();
	printf("MUSIC TESTS COMPLETE.\n");
    return 0;
}