/*
File Name: synch.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Processes synchronous clock-tick updates for score, movement, and collision.
*/

#include "synch.h"
#include "cond.h"

signed int onClockTick(GameMdl *model)
{
    model->score += 1;

    if (model->dino) {
        moveDino(model->dino);
    }
    if (model->cactus) {
        moveCactus(model->cactus);
    }
    if (checkCollision(model)) {
        onCollision(model);
        return 1;
    }
    return 0;
}

