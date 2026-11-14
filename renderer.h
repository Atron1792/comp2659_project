#ifndef RENDERER_H
#define RENDERER_H

#include "model.h"
#include "TYPES.H"
#include "raster.h"
#include "bitmaps.h"

void render(const GameMdl *model);

void renderGround(const GameMdl *model);
void renderDino(const Dino *dino, UINT32 *base);
void renderCactus(const Cactus *cactus, UINT32 *base);

void renderScore(UINT32 score, UINT32* base);

void disableCursor();
#endif