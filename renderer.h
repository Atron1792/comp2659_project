#ifndef RENDERER_H
#define RENDERER_H

#include "model.h"
#include "TYPES.H"

void render(const GameMdl *model);

void renderDino(const Dino *dino, UINT32 *base);

void renderCactus(const Cactus *cactus, UINT32 *base);

#endif