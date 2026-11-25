/*
File Name: effects.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Implements gameplay sound effects using the PSG module.
*/

#include "effects.h"
#include "psg.h"

void playJumpEffect()
{
    setTone(CHANNEL_C, JUMP_TONE_PERIOD);
    enableChannel(CHANNEL_C, TONE_ON, NOISE_OFF);

    setEnvelope(HOLD, JUMP_ENVELOPE_PERIOD);
    writePsg(C_vol, ENVELOPE_VOLUME);
}

void playCollisionEffect()
{
    setNoise(COLLISION_NOISE_PERIOD);
    enableChannel(CHANNEL_C, TONE_OFF, NOISE_ON);

    setEnvelope(HOLD, COLLISION_ENVELOPE_PERIOD);
    writePsg(C_vol, ENVELOPE_VOLUME);
}