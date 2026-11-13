#include "cond.h"

void onCollision(GameMdl *model)
{
    model->gameStatus |= LOSS_FLG;
}