#include "cond.h"

void on_collision(GameMdl *model)
{
    model->gameStatus |= LOSS_FLG;
}