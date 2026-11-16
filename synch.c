/*
File Name: synch.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Processes synchronous clock-tick updates for score and object movement.
*/

#include "synch.h"

static UINT16 scoreTickCount;

void onClockTick(GameMdl *model)
{
    if (model->gameStatus) {
        return;
    }

    scoreTickCount++;
    if (scoreTickCount >= 7) {
        model->score += 1;
        scoreTickCount = 0;
    }

    if (model->dino) {
        moveDino(model->dino);
    }
    if (model->cactus) {
        moveCactus(model->cactus);
    }
}

