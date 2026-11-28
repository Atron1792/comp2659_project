/*
File Name: psg.h
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Declares the PSG (Programmable Sound Generator) functionality for the game.
*/

#ifndef PSG
#define PSG

#include <osbind.h>
#include "TYPES.H"

/* YM2149 memory mapped addresses */
#define SELECT_REG 0xFF8800
#define WRITE_REG 0xFF8802


/* YM2149 register constants */
#define A_fine 0x00
#define A_coarse 0x01
#define B_fine 0x02
#define B_coarse 0x03
#define C_fine 0x04
#define C_coarse 0x05
#define NOISE 0x06
#define MIXER_IO 0x07
#define A_vol 0x08
#define B_vol 0x09
#define C_vol 0x0A
#define ENVELOPE_FINE 0x0B
#define ENVELOPE_COARSE 0x0C
#define ENVELOPE_SHAPE 0X0D
#define PORT_A 0x0E
#define PORT_B 0x0F

/**** Defined constants for function parameters ****/

/* Channels */
#define CHANNEL_A 0
#define CHANNEL_B 1
#define CHANNEL_C 2

/* Tone and noise state */
#define TONE_ON 1
#define TONE_OFF 0
#define NOISE_ON 1
#define NOISE_OFF 0

/* Masks for MIX_IO */
#define TONE_A_ON 0xFE
#define TONE_B_ON 0xFD
#define TONE_C_ON 0xFB
#define TONE_A_OFF 0x01
#define TONE_B_OFF 0x02
#define TONE_C_OFF 0x04
#define NOISE_A_ON 0xF7
#define NOISE_B_ON 0xEF
#define NOISE_C_ON 0xDF
#define NOISE_A_OFF 0x08
#define NOISE_B_OFF 0x10
#define NOISE_C_OFF 0x20


/* Envelop shapes */
#define HOLD 0
#define ALT 1
#define ATT 2
#define CONT 3


/* ----- Function: readPsg -----

 PURPOSE: Reads a PSG register when the register and output pointer are valid.

 INPUT: reg(UINT8) - PSG register number in the range 0 through 15.
        value(UINT8 *) - Destination for the read register value.

 OUTPUT: int - Nonzero on success; zero if reg or value is invalid.

 ASSUMPTIONS: Supervisor mode is briefly enabled while the PSG is accessed.
*/
int readPsg(UINT8 reg, UINT8 *value);

/* ----- Function: writePsg -----

 PURPOSE: Writes a byte to a valid PSG register.

 INPUT: reg(UINT8) - PSG register number in the range 0 through 15.
        val(UINT8) - Eight-bit value to write.

 OUTPUT: None

 ASSUMPTIONS: Supervisor mode is briefly enabled while the PSG is accessed.
*/
void writePsg(UINT8 reg, UINT8 val);

/* ----- Function: setTone -----

 PURPOSE: Loads the fine and coarse tone registers for a valid PSG channel.

 INPUT: channel(UINT8) - Channel A, B, or C.
        tuning(UINT16) - Twelve-bit tone period in the range 0 through 4095.

 OUTPUT: None

 ASSUMPTIONS: An out-of-range tuning or channel value is ignored.
*/
void setTone(UINT8 channel, UINT16 tuning);

/* ----- Function: setVolume -----

 PURPOSE: Sets a valid PSG channel volume.

 INPUT: channel(UINT8) - Channel A, B, or C.
        volume(UINT8) - Volume in the range 0 through 15.

 OUTPUT: None

 ASSUMPTIONS: An out-of-range channel or volume value is ignored.
*/
void setVolume(UINT8 channel, UINT8 volume);

/* ----- Function: enableChannel -----

 PURPOSE: Enables or disables a channel's tone and noise mixer signals.

 INPUT: channel(UINT8) - Channel A, B, or C.
        toneOn(UINT8) - TONE_ON or TONE_OFF.
        noiseOn(UINT8) - NOISE_ON or NOISE_OFF.

 OUTPUT: None

 ASSUMPTIONS: An invalid channel or signal value is ignored.
*/
void enableChannel(UINT8 channel, UINT8 toneOn, UINT8 noiseOn);

/* ----- Function: setNoise -----

 PURPOSE: Loads the PSG noise-period register.

 INPUT: tuning(UINT8) - Five-bit noise period in the range 0 through 31.

 OUTPUT: None

 ASSUMPTIONS: An out-of-range tuning value is ignored.
*/
void setNoise(UINT8 tuning);

/* ----- Function: setEnvelope -----

 PURPOSE: Loads a valid envelope shape and sixteen-bit sustain period.

 INPUT: shape(UINT8) - HOLD, ALT, ATT, or CONT.
        sustain(UINT16) - Sixteen-bit envelope period.

 OUTPUT: None

 ASSUMPTIONS: An unsupported envelope shape is ignored.
*/
void setEnvelope(UINT8 shape, UINT16 sustain);

/* ----- Function: stopSound -----

 PURPOSE: Silences all PSG tone, noise, and envelope output.

 INPUT: None

 OUTPUT: None

 ASSUMPTIONS: All channels may be safely reset.
*/
void stopSound();
#endif
