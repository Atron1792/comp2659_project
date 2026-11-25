/*
File Name: cond.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Provides collision detection and game-status condition handlers.
*/

#include "cond.h"

signed int checkCollision(const GameMdl *model)
{
    if (model->dino && model->cactus) {
        if (model->dino->x < model->cactus->x + CACTUS_HITBOX_WIDTH &&
            model->dino->x + DINO_HITBOX_WIDTH > model->cactus->x &&
            model->dino->y < model->cactus->y + CACTUS_HITBOX_HEIGHT &&
            model->dino->y + DINO_HITBOX_HEIGHT > model->cactus->y) {
            return 1;
        }
    }
    return 0;
}

void onCollision(GameMdl *model)
{
    model->gameStatus |= LOSS_FLG;
    if (model->dino) {
        model->dino->isDead = 1;
    }
    playCollisionEffect();
}

void onQuit(GameMdl* model) {
    model -> gameStatus |= QUIT_FLG;
}
