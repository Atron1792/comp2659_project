#ifndef RENDERER_H
#define RENDERER_H

#include "model.h"
#include "types.h"

void render(const GameMdl *model, UINT32 *base);

void renderDino(const Dino *dino, UINT16 *base);

void renderCactus(const Cactus *cactus, UINT16 *base);

#endif