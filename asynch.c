#include "asynch.h"

void onJumpRequest(GameMdl *model)
{
    if (model->dino &&
        model->dino->y >= DINO_Y_POS &&
        model->dino->yVel >= 0) {
        model->dino->y = DINO_Y_POS;
        model->dino->yVel = -JUMP_Y_VELOCITY;
    }
}

void onQuitRequest(GameMdl *model)
{
    model->gameStatus |= QUIT_FLG;
}