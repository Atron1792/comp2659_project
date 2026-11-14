#ifndef GAME_H
#define GAME_H

/* Includes */
#include <osbind.h>
#include <stdio.h>
#include <stdlib.h>

#include "TYPES.H"
#include "renderer.h"
#include "model.h"

UINT32 getTime();

void gameLoop(GameMdl* model);
void initScreen(GameMdl* model);

#endif