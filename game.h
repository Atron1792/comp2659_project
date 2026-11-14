#ifndef GAME_H
#define GAME_H

/* Includes */
#include <osbind.h>
#include <stdio.h>
#include <stdlib.h>

#include "TYPES.H"
#include "raster.h"
#include "renderer.h"
#include "model.h"
#include "asynch.h"
#include "synch.h"
#include "cond.h"

UINT32 getTime();

void gameInit(GameMdl* model);
void gameLoop(GameMdl* model);
void initScreen(GameMdl* model);

#endif