/*
File Name: tst_psg.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Demonstrates usage of the low-level PSG module.
*/

#include <osbind.h>
#include <stdio.h>

#include "psg.h"
#include "TYPES.H"

/*----- Function: tstReadPsg -----

 PURPOSE: Exercises reading a PSG register.

 INPUT: None.

 OUTPUT: None.
*/
static void tstReadPsg()
{
	UINT8 value;

	printf("read valid register: %d\n", readPsg(MIXER_IO, &value));
	printf("read invalid register: %d\n", readPsg(16, &value));
	printf("read null destination: %d\n", readPsg(MIXER_IO, (UINT8 *)0));
}

/*----- Function: tstWritePsg -----

 PURPOSE: Exercises writing a PSG register.

 INPUT: None.

 OUTPUT: None.
*/
static void tstWritePsg()
{
	UINT8 value;

	writePsg(A_vol, 9);
	readPsg(A_vol, &value);
	printf("write valid register: volume = %u\n", value);

	writePsg(16, 15);
	printf("invalid register write ignored\n");
}

/*----- Function: tstSetTone -----

 PURPOSE: Exercises configuring tone frequency on each PSG channel.

 INPUT: None.

 OUTPUT: None.
*/
static void tstSetTone()
{
	UINT8 fine;
	UINT8 coarse;

	setTone(CHANNEL_A, 0x0ABC);
	readPsg(A_fine, &fine);
	readPsg(A_coarse, &coarse);
	printf("tone valid: fine = %u, coarse = %u\n", fine, coarse);

	setTone(CHANNEL_C, 4095);
	readPsg(C_fine, &fine);
	readPsg(C_coarse, &coarse);
	printf("tone C maximum: fine = %u, coarse = %u\n", fine, coarse);

	setTone(CHANNEL_C, 4096);
}

/*----- Function: tstSetVolume -----

 PURPOSE: Exercises configuring volume on each PSG channel.

 INPUT: None.

 OUTPUT: None.
*/
static void tstSetVolume()
{
	UINT8 value;

	setVolume(CHANNEL_B, 12);
	readPsg(B_vol, &value);
	printf("volume valid: channel B = %u\n", value);

	setVolume(CHANNEL_B, 16);
}

/*----- Function: tstEnableChannel -----

 PURPOSE: Exercises enabling and disabling channel tone and noise signals.

 INPUT: None.

 OUTPUT: None.
*/
static void tstEnableChannel()
{
	UINT8 mixer;

	enableChannel(CHANNEL_A, TONE_ON, NOISE_OFF);
	readPsg(MIXER_IO, &mixer);
	printf("channel A tone on: mixer = %u\n", mixer);

	enableChannel(CHANNEL_C, TONE_OFF, NOISE_ON);
	readPsg(MIXER_IO, &mixer);
	printf("channel C noise on: mixer = %u\n", mixer);

	enableChannel(3, TONE_ON, NOISE_ON);
}

/*----- Function: tstSetNoise -----

 PURPOSE: Exercises configuring the PSG noise generator.

 INPUT: None.

 OUTPUT: None.
*/
static void tstSetNoise()
{
	UINT8 value;

	setNoise(31);
	readPsg(NOISE, &value);
	printf("noise valid: %u\n", value);

	setNoise(32);
}

/*----- Function: tstSetEnvelope -----

 PURPOSE: Exercises configuring the PSG envelope generator.

 INPUT: None.

 OUTPUT: None.
*/
static void tstSetEnvelope()
{
	UINT8 fine;
	UINT8 coarse;
	UINT8 shape;

	setEnvelope(HOLD, 0x1234);
	readPsg(ENVELOPE_FINE, &fine);
	readPsg(ENVELOPE_COARSE, &coarse);
	readPsg(ENVELOPE_SHAPE, &shape);
	printf("envelope hold: fine = %u, coarse = %u, shape = %u\n", fine, coarse, shape);

	setEnvelope(99, 0xFFFF);
}

/*----- Function: tstStopSound -----

 PURPOSE: Exercises silencing all PSG sound production.

 INPUT: None.

 OUTPUT: None.
*/
static void tstStopSound()
{
	UINT8 mixer;
	UINT8 volume;

	stopSound();
	readPsg(MIXER_IO, &mixer);
	readPsg(A_vol, &volume);
	printf("stop sound: mixer = %u, volume A = %u\n", mixer, volume);
}

/*----- Function: main -----

 PURPOSE: Runs the PSG-module test cases.

 INPUT: None.

 OUTPUT: Returns zero after the test cases complete.
*/
int main()
{
	tstReadPsg();
	Cconin();
	tstWritePsg();
	Cconin();
	tstSetTone();
	Cconin();
	tstSetVolume();
	Cconin();
	tstEnableChannel();
	Cconin();
	tstSetNoise();
	Cconin();
	tstSetEnvelope();
	Cconin();
	tstStopSound();
	printf("PSG TESTS COMPLETE.\n");
    return 0;
}