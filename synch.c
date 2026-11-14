#include "synch.h"
#include "cond.h"

signed int onClockTick(GameMdl *model)
{
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

