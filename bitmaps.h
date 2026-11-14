/*
File Name: bitmaps.h
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Declares shared dimensions and bitmap data for game sprites.
*/

#ifndef BITMAPS_H
#define BITMAPS_H

#include "TYPES.H"

#define DINO_WIDTH 32
#define DINO_HEIGHT 32
#define CACTUS_WIDTH 32
#define CACTUS_HEIGHT 32

/* Dinosaur animation frames, each containing DINO_HEIGHT 32-bit rows. */
extern const UINT32 dinoBitmap0[DINO_HEIGHT];
extern const UINT32 dinoBitmap1[DINO_HEIGHT];
extern const UINT32 dinoBitmap2[DINO_HEIGHT];
extern const UINT32 dinoBitmapDeath[DINO_HEIGHT];

/* Cactus sprite, containing CACTUS_HEIGHT 32-bit rows. */
extern const UINT32 cactusBitmap[CACTUS_HEIGHT];

#endif