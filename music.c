/*
File Name: music.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Implements looping background music using the PSG module.
*/

#include "music.h"

static const MusicNote backgroundBeat[MUSIC_NOTE_COUNT] = {
    {268, 9}, {358, 3}, {268, 6}, {358, 6},
    {179, 3}, {536, 9}, {358, 6}, {451, 6},
    {358, 6}, {402, 6}, {451, 6}, {268, 6},
    {179, 3}, {358, 9}, {402, 6}, {451, 6}
};

static UINT16 currentNote;
static UINT32 ticksRemaining;
static int musicPlaying;

void startMusic()
{
    currentNote = 0;
    ticksRemaining = (backgroundBeat[currentNote].duration * MUSIC_TEMPO_SCALE);
    musicPlaying = 1;

    enableChannel(CHANNEL_A, TONE_ON, NOISE_OFF);
    setTone(CHANNEL_A, backgroundBeat[currentNote].tuning);
    setVolume(CHANNEL_A, MUSIC_VOLUME);
}

void stopMusic()
{
    musicPlaying = 0;
    enableChannel(CHANNEL_A, TONE_OFF, NOISE_OFF);
    setVolume(CHANNEL_A, 0);
}

void updateMusic(UINT32 timeElapsed)
{
    if (!musicPlaying)
	{
        return;
    }

    while (timeElapsed >= ticksRemaining) {
        timeElapsed -= ticksRemaining;
        currentNote++;

        if (currentNote >= MUSIC_NOTE_COUNT) {
            currentNote = 0;
        }

        ticksRemaining = (backgroundBeat[currentNote].duration * MUSIC_TEMPO_SCALE);

        setTone(CHANNEL_A, backgroundBeat[currentNote].tuning);
        setVolume(CHANNEL_A, MUSIC_VOLUME);
    }

    ticksRemaining -= timeElapsed;
}