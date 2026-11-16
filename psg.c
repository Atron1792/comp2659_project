#include "psg.h"

volatile UINT8 *PSG_select = (volatile UINT8 *)SELECT_REG;
volatile UINT8 *PSG_write = (volatile UINT8 *)WRITE_REG;

bool read_psg(UINT8 reg, UINT8 &value) {
	long old_ssp;
	if (reg <= 15) {
		old_ssp = Super(0);
		*PSG_select = reg;
		value = *PSG_select;
		Super(old_ssp);
		return true;
	}
	return false;
}

void write_psg(UINT8 reg, UINT8 val) {
	long old_ssp = Super(0);
	if (reg <= 15) {
		*PSG_select = reg;
		*PSG_write = val;
	}
	Super(old_ssp);
}

void set_tone(UINT8 channel, UINT16 tuning) {
	UINT16 fine = tuning;
	UINT16 coarse = tuning;

	if (CHANNEL_A <= channel && channel <= CHANNEL_C && tuning <= 4095){
		fine &= 0x00FF; /* capture the bottom 8 bits of 12 through masking */
		coarse >>= 8; /* capture the top 4 bits of 12 through right shifting */
		course &= 0x00F;
		
		switch (channel) {
			case CHANNEL_A:
				write_psg(A_fine, fine);
				write_psg(A_coarse, coarse);
				break;
			
			case CHANNEL_B:
				write_psg(B_fine, fine);
				write_psg(B_coarse, coarse);
				break;
			
			case CHANNEL_C:
				write_psg(C_fine, fine);
				write_psg(C_coarse, coarse);
				break;
			
			default:
				break;
		}
	}
}

void set_volume(UINT8 channel, UINT8 volume) {
	if (channel >= CHANNEL_A && /* Channel A */
		channel <= CHANNEL_C && /* Channel C */
		volume >= 0 && 
		volume <= 15
	) {
		write_psg(A_vol + channel, volume);
	}
}

void enable_channel(UINT8 channel, UINT8 tone_on, UINT8 noise_on) {
	UINT8 maskTune;

	if (channel > CHANNEL_C) {
		return;
	}

	if (!read_psg(MIXER_IO, maskTune)) {
		return;
	}
		
	switch (channel) {
		case CHANNEL_A:
			if (tone_on > 0) {
				write_psg(MIXER_IO, TONE_A_ON);
			} else {
				write_psg(MIXER_IO, TONE_A_OFF);
			}
			if (noise_on > 0) {
				write_psg(MIXER_IO, NOISE_A_ON);
			} else {
				write_psg(MIXER_IO, NOISE_A_OFF);
			}
			break;
		case CHANNEL_B:
			if (tone_on) {
				write_psg(MIXER_IO, TONE_B_ON);
			} else {
				write_psg(MIXER_IO, TONE_B_OFF);
			}
			if (noise_on > 0) {
				write_psg(MIXER_IO, NOISE_B_ON);
			} else {
				write_psg(MIXER_IO, NOISE_B_OFF);
			}
			break;
		case CHANNEL_C:
			if (tone_on) {
				write_psg(MIXER_IO, TONE_C_ON);
			} else if (noiseOn) {
				write_psg(MIXER_IO, NOISE_C_ON);
			}
			if (noise_on > 0) {
				write_psg(MIXER_IO, NOISE_C_ON);
			} else {
				write_psg(MIXER_IO, NOISE_C_OFF);
			}
			break;
		
		default:
			break;
	}
}

void set_noise(UINT8 tuning) {
	if (tuning <= 31) {
		write_psg(NOISE, tuning);
	}
}

void set_envelope(UINT8 shape, UINT16 sustain) {
	int fine = sustain & 0x00FF;
	int coarse = sustain >> 8;

	switch (shape) {
		case HOLD:
			write_psg(ENVELOPE_SHAPE, 1);
			write_psg(ENVELOPE_FINE, fine);
			write_psg(ENVELOPE_COARSE, coarse);
			break;

		case ALT:
			write_psg(ENVELOPE_SHAPE, 2);
			write_psg(ENVELOPE_FINE, fine);
			write_psg(ENVELOPE_COARSE, coarse);
			break;

		case ATT:
			write_psg(ENVELOPE_SHAPE, 4);
			write_psg(ENVELOPE_FINE, fine);
			write_psg(ENVELOPE_COARSE, coarse);
			break;

		case CONT:
			write_psg(ENVELOPE_SHAPE, 8);
			write_psg(ENVELOPE_FINE, fine);
			write_psg(ENVELOPE_COARSE, coarse);
			break;
	}
}

void stop_sound() {
	int reg;
	for (reg = 0; reg <= 0xF; reg++) {
		if (reg == 7) {
			write_psg(MIXER_IO, 0x3F); /* Disable tone & noise on all channels */
		} else {
			write_psg(reg, 0); /* reduce all pitch data to 0 */
		}
	}
}
