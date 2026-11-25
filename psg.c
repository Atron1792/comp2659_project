/*
File Name: psg.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Implements the PSG (Programmable Sound Generator) functionality for the game.
*/

#include "psg.h"

volatile UINT8 *psgSelect = (volatile UINT8 *)SELECT_REG;
volatile UINT8 *psgWrite = (volatile UINT8 *)WRITE_REG;

int readPsg(UINT8 reg, UINT8 *value)
{
	long oldSsp;

	if (value == 0 || reg > 15)
	{
		return 0;
	}

	oldSsp = Super(0);
	*psgSelect = reg;
	*value = *psgSelect;
	Super(oldSsp);
	return 1;
}

void writePsg(UINT8 reg, UINT8 val)
{
	long oldSsp;

	if (reg > 15) {
		return;
	}

	oldSsp = Super(0);
	*psgSelect = reg;
	*psgWrite = val;
	Super(oldSsp);
}

void setTone(UINT8 channel, UINT16 tuning)
{
	UINT16 fine = tuning;
	UINT16 coarse = tuning;

	if (CHANNEL_A <= channel && channel <= CHANNEL_C && tuning <= 4095) {
		fine = (tuning & 0x00FF);
		coarse = ((tuning >> 8) & 0x000F);

		if (channel == CHANNEL_A)
		{
			writePsg(A_fine, fine);
			writePsg(A_coarse, coarse);
		} else if (channel == CHANNEL_B)
		{
			writePsg(B_fine, fine);
			writePsg(B_coarse, coarse);
		} else
		{
			writePsg(C_fine, fine);
			writePsg(C_coarse, coarse);
		}
	}
}

void setVolume(UINT8 channel, UINT8 volume)
{
	if (channel >= CHANNEL_A && channel <= CHANNEL_C && volume >= 0 && volume <= 15)
	{
		writePsg((A_vol + channel), volume);
	}
}

void enableChannel(UINT8 channel, UINT8 toneOn, UINT8 noiseOn)
{
	UINT8 mixer;
	UINT8 toneMask;
	UINT8 noiseMask;

	if (channel > CHANNEL_C || toneOn > TONE_ON || noiseOn > NOISE_ON) {
		return;
	}

	if (!readPsg(MIXER_IO, &mixer)) {
		return;
	}

	toneMask = (1 << channel);
	noiseMask = (8 << channel);

	if (toneOn) {
		mixer &= (~toneMask);
	} else {
		mixer |= toneMask;
	}

	if (noiseOn) {
		mixer &= (~noiseMask);
	} else {
		mixer |= noiseMask;
	}
	writePsg(MIXER_IO, mixer);
}

void setNoise(UINT8 tuning)
{
	if (tuning <= 31) {
		writePsg(NOISE, tuning);
	}
}

void setEnvelope(UINT8 shape, UINT16 sustain)
{
	UINT8 fine;
	UINT8 coarse;

	if (shape != HOLD && shape != ALT && shape != ATT && shape != CONT) {
		return;
	}

	fine = (sustain & 0x00FF);
	coarse = (sustain >> 8);

	writePsg(ENVELOPE_FINE, fine);
	writePsg(ENVELOPE_COARSE, coarse);

	if (shape == HOLD)
	{
		writePsg(ENVELOPE_SHAPE, 1);
	} else if (shape == ALT)
	{
		writePsg(ENVELOPE_SHAPE, 2);
	} else if (shape == ATT)
	{
		writePsg(ENVELOPE_SHAPE, 4);
	} else {
		writePsg(ENVELOPE_SHAPE, 8);
	}
}

void stopSound()
{
	int reg;

	writePsg(MIXER_IO, 0x3F);

	for (reg = 0; reg <= 10; reg++) {
		writePsg((UINT8)reg, 0);
	}
	
	writePsg(ENVELOPE_FINE, 0);
	writePsg(ENVELOPE_COARSE, 0);
	writePsg(ENVELOPE_SHAPE, 0);
}
