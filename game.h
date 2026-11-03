#ifndef GAME_H
#define GAME_H

/* Includes */
#include <osbind.h>
#include <stdio.h>
#include <stdlib.h>

#include "TYPES.H"
#include "model.h"

void gameLoop(GameModel* model);
void initScreen(GameModel* model);

#endif