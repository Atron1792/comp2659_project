/*
File Name: psg.h
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Declares the PSG (Programmable Sound Generator) functionality for the game.
*/

#ifndef PSG
#define PSG

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
#define PORT_B 0x0B

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
#define TONE_A_ON 0x3E
#define TONE_B_ON 0x3D
#define TONE_C_ON 0x3B
#define TONE_A_OFF 0x01
#define TONE_B_OFF 0x02
#define TONE_C_OFF 0x04

#define NOISE_A_ON 0xEF
#define NOISE_B_ON 0xDF
#define NOISE_C_ON 0xBF
#define NOISE_A_OFF 0x08
#define NOISE_B_OFF 0x10
#define NOISE_C_OFF 0x20


/* Envelop shapes */
#define HOLD 0
#define ALT 1
#define ATT 2
#define CONT 3


/* ----- Function: readPsg -----
Purpose: Attempts to read a value from the given PSG register (0-15). This is a helper
         routine that will be helpful to test the other routines in this module.

Input: reg(UINT8) - The register that is being read from
       value(UINT8*) - The value that was read from the register
                       value is valid, if and only if the output is true

Output: Boolean indicating if a value was successfully read or not
*/
int readPsg(UINT8 reg, UINT8 *value);

/* ----- Function: writePsg -----
Purpose: Writes the given byte value (0-255) to the given PSG register (0-15). This is a helper
         routine to be used by the other functions in this module.

Input: reg(UINT8) - Register that is being written to
       val(UINT8) - Value being written to reg

Output: None
*/
void writePsg(UINT8 reg, UINT8 val);

/* ----- Function: setTone -----
Purpose: Loads the tone registers (coarse and fine) for the given channel (0=A, 1=B, 2=C)
         with the given {12-bit} tuning.


Input: channel(UINT8) - The channel (A, B, or C) that is being written to
       tuning(UINT16) - 12-bit tone that will be written to the specified channel

Output: None
*/
void setTone(UINT8 channel, UINT16 tuning);

/* ----- Function: setVolume -----
Purpose: Writes the given byte value (0-255) to the given PSG register (0-15). This is a helper
         routine to be used by the other functions in this module.

Input: channel(UINT8) - The channel (A, B, or C) that is being written to
       volume(UINT8) - The volume value to be written to specified channel

Output: None
*/
void setVolume(UINT8 channel, UINT8 volume);

/* ----- Function: enableChannel -----
Purpose: Turns the given channel’s (0=A, 1=B, 2=C) tone/noise signals on/off (0=off, 1=on).

Input: channel(UINT8) - The channel (A, B, or C) that is being written to
       toneOn(UINT8) - Set the tone for the specified channel to be either on or off
       noiseOn(UINT8) - Set the noise for the specified channel to be either on or off

Output: None
*/
void enableChannel(UINT8 channel, UINT8 toneOn, UINT8 noiseOn);

/* ----- Function: setNoise -----
Purpose: Load the Noise register with the given tuning.

Input: tuning(UINT8) - The 5-bit tuning value loaded to the noise register

Output: None
*/
void setNoise(UINT8 tuning);

/* ----- Function: setEnvelope -----
Purpose: Loads the PSG envelope control registers with the given envelope shape and 16-bit sustain.

Input: shape(UINT8) - The shape loaded into the envelope control registers
       sustain(UINT16) - The sustain value being written to the envelope control registers

Output: None
*/
void setEnvelope(UINT8 shape, UINT16 sustain);

/* ----- Function: stopSound -----
Purpose: Silences all PSG sound production.

Input: None

Output: None
*/
void stopSound();
#endif
