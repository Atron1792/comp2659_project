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
#define TONE_A_ON 0x3E /*62*/
#define TONE_B_ON 0x3D /*61*/
#define TONE_C_ON 0x3B /*59*/
#define NOISE_A_ON 0xEF
#define NOISE_B_ON 0xDF
#define NOISE_C_ON 0xBF

#define TONE_A_OFF 0x01
#define TONE_B_OFF 0x02
#define TONE_C_OFF 0x04
#define NOISE_A_OFF 0x08
#define NOISE_B_OFF 0x10
#define NOISE_C_OFF 0x20

/* Envelop shapes */
#define HOLD 0
#define ALT 1
#define ATT 2
#define CONT 3


/* ----- Function: read_psg -----
Purpose: Attempts to read a value from the given PSG register (0-15). This is a helper
         routine that will be helpful to test the other routines in this module.

Input: Register(UINT8) - The register that is being read from
       Value(UINT8&) - The value that was read from the register
                       Value is valid, if and only if the output is true

Output: Boolean indicating if a value was successfully read or not
*/
bool read_psg(UINT8 reg, UINT8 &value);

/* ----- Function: write_psg -----
Purpose: Writes the given byte value (0-255) to the given PSG register (0-15). This is a helper
         routine to be used by the other functions in this module.

Input: Register(UINT8) - Register that is being written to
       Value(UINT8) - Value being written to reg

Output: None
*/
void write_psg(UINT8 reg, UINT8 val);

/* ----- Function: set_tone -----
Purpose: Loads the tone registers (coarse and fine) for the given channel (0=A, 1=B, 2=C)
         with the given {12-bit} tuning.


Input: Channel(UINT8) - The channel (A, B, or C) that is being written to
       Tunning(UINT16) - 12-bit tone that will be written to the specified channel

Output: None
*/
void set_tone(UINT8 channel, UINT16 tuning);

/* ----- Function: set_volume -----
Purpose: Writes the given byte value (0-255) to the given PSG register (0-15). This is a helper
         routine to be used by the other functions in this module.

Input: Channel(UINT8) - The channel (A, B, or C) that is being written to
       Volume(UINT8) - The volume value to be written to specified channel

Output: None
*/
void set_volume(UINT8 channel, UINT8 volume);

/* ----- Function: enable_channel -----
Purpose: Turns the given channel’s (0=A, 1=B, 2=C) tone/noise signals on/off (0=off, 1=on).

Input: Channel(UINT8) - The channel (A, B, or C) that is being written to
       Tone(UINT8) - Set the tone for the specified channel to be either on or off
       Noise(UINT8) - Set the noise for the specified channel to be either on or off

Output: None
*/
void enable_channel(UINT8 channel, UINT8 tone_on, UINT8 noise_on);

/* ----- Function: set_noise -----
Purpose: Load the Noise register with the given tuning.

Input: Tunning(UINT8) - The 5-bit tuning value loaded to the noise register

Output: None
*/
void set_noise(UINT8 tuning);

/* ----- Function: set_envelope -----
Purpose: Loads the PSG envelope control registers with the given envelope shape and 16-bit sustain.

Input: Shape(UINT8) - The shape loaded into the envelope control registers
       Sustain(UINT16) - The sustain value being written to the envelope control registers

Output: None
*/
void set_envelope(UINT8 shape, UINT16 sustain);

/* ----- Function: stop_sound -----
Purpose: Silences all PSG sound production.

Input: None

Output: None
*/
void stop_sound();
#endif