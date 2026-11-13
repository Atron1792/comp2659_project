#include "asynch.h"

void on_jump_request(GameMdl *model)
{
    if (model->dino) {
        if (model->dino->y == DINO_Y_POS) {
            model->dino->yVel = -JUMP_Y_VELOCITY;
        }
    }
}

void on_quit_request(GameMdl *model)
{
    model->gameStatus |= QUIT_FLG;
}