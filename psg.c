/*
File Name: psg.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Implements the PSG (Programmable Sound Generator) functionality for the game.
*/

#include "psg.h"
#include "TYPES.H"

volatile UINT8 *psgSelect = (volatile UINT8 *)SELECT_REG;
volatile UINT8 *psgWrite = (volatile UINT8 *)WRITE_REG;

int readPsg(UINT8 reg, UINT8 *value) {
	long oldSsp;
	if (reg <= 15) {
		oldSsp = Super(0);
		*psgSelect = reg;
		*value = *psgSelect;
		Super(oldSsp);
		return 1;
	}
	return 0;
}

void writePsg(UINT8 reg, UINT8 val) {
	long oldSsp = Super(0);
	if (reg <= 15) {
		*psgSelect = reg;
		*psgWrite = val;
	}
	Super(oldSsp);
}

void setTone(UINT8 channel, UINT16 tuning) {
	UINT16 fine = tuning;
	UINT16 coarse = tuning;

	if (CHANNEL_A <= channel && channel <= CHANNEL_C && tuning <= 4095){
		fine &= 0x00FF; /* capture the bottom 8 bits of 12 through masking */
		coarse >>= 8; /* capture the top 4 bits of 12 through right shifting */
		coarse &= 0x00F;

		switch (channel) {
			case CHANNEL_A:
				writePsg(A_fine, fine);
				writePsg(A_coarse, coarse);
				break;

			case CHANNEL_B:
				writePsg(B_fine, fine);
				writePsg(B_coarse, coarse);
				break;

			case CHANNEL_C:
				writePsg(C_fine, fine);
				writePsg(C_coarse, coarse);
				break;

			default:
				break;
		}
	}
}

void setVolume(UINT8 channel, UINT8 volume) {
	if (channel >= CHANNEL_A && /* Channel A */
		channel <= CHANNEL_C && /* Channel C */
		volume >= 0 &&
		volume <= 15
	) {
		writePsg(A_vol + channel, volume);
	}
}

void enableChannel(UINT8 channel, UINT8 toneOn, UINT8 noiseOn) {
	UINT8 maskTune;

	if (channel > CHANNEL_C) {return;} /* Invalid channel */
	if (!readPsg(MIXER_IO, maskTune)) {return;} /* Unable to read psg chip */
		
	switch (channel) {
		case CHANNEL_A:
			if (toneOn) {
				maskTune &= TONE_A_ON;
			} else {
				maskTune |= ~TONE_A_ON;
			}
			if (noiseOn) {
				maskTune &= NOISE_A_ON;
			} else {
				maskTune |= ~NOISE_A_ON;
			}
			break;
		case CHANNEL_B:
			if (toneOn) {
				maskTune &= TONE_B_ON;
			} else {
				maskTune |= ~TONE_B_ON;;
			}
			if (noiseOn) {
				maskTune &= NOISE_B_ON;
			} else {
				maskTune |= ~NOISE_B_ON;
			}
			break;
		case CHANNEL_C:
			if (toneOn) {
				maskTune &= TONE_C_ON;
			} else {
				maskTune |= ~TONE_C_ON;
			}
			if (noiseOn) {
				maskTune &= NOISE_C_ON;
			} else {
				maskTune |= ~NOISE_C_ON;
			}
			break;

		default:
			break;
	}
	writePsg(MIXER_IO, maskTune);
}

void setNoise(UINT8 tuning) {
	if (tuning <= 31) {
		writePsg(NOISE, tuning);
	}
}

void setEnvelope(UINT8 shape, UINT16 sustain) {
	int fine = sustain & 0x00FF;
	int coarse = sustain >> 8;

	switch (shape) {
		case HOLD:
			writePsg(ENVELOPE_SHAPE, 1);
			writePsg(ENVELOPE_FINE, fine);
			writePsg(ENVELOPE_COARSE, coarse);
			break;

		case ALT:
			writePsg(ENVELOPE_SHAPE, 2);
			writePsg(ENVELOPE_FINE, fine);
			writePsg(ENVELOPE_COARSE, coarse);
			break;

		case ATT:
			writePsg(ENVELOPE_SHAPE, 4);
			writePsg(ENVELOPE_FINE, fine);
			writePsg(ENVELOPE_COARSE, coarse);
			break;

		case CONT:
			writePsg(ENVELOPE_SHAPE, 8);
			writePsg(ENVELOPE_FINE, fine);
			writePsg(ENVELOPE_COARSE, coarse);
			break;
	}
}

void stopSound() {
	int reg;
	for (reg = 0; reg <= 0xF; reg++) {
		if (reg == 7) {
			writePsg(MIXER_IO, 0x3F); /* Disable tone & noise on all channels */
		} else {
			writePsg(reg, 0); /* reduce all pitch data to 0 */
		}
	}
}
