#include <assert.h>
#include <stdio.h>

#include "asynch.h"
#include "cond.h"
#include "synch.h"

static void initTestModel(GameMdl *model, Dino *dino, Cactus *cactus)
{
    model->score = 0L;
    model->gameStatus = GAME_ON_FLG;
    model->dino = dino;
    model->cactus = cactus;
    model->base = (UINT16 *)0;

    initDino(dino, 0, 0, DINO_X_POS, DINO_Y_POS, 0, 0, 0);
    initCactus(cactus, 320, DINO_Y_POS, 0, 0);
}

static void tstJumpRequest(void)
{
    GameMdl model;
    Dino dino;
    Cactus cactus;

    initTestModel(&model, &dino, &cactus);

    onJumpRequest(&model);
    assert(dino.yVel == -JUMP_Y_VELOCITY);

    dino.y = DINO_Y_POS - 1;
    dino.yVel = 0;
    onJumpRequest(&model);
    assert(dino.yVel == 0);
}

static void tstQuitRequest(void)
{
    GameMdl model;
    Dino dino;
    Cactus cactus;

    initTestModel(&model, &dino, &cactus);

    onQuitRequest(&model);
    assert((model.gameStatus & QUIT_FLG) != 0);
}

static void tstClockTick(void)
{
    GameMdl model;
    Dino dino;
    Cactus cactus;
    int oldDinoY;
    int oldCactusX;

    initTestModel(&model, &dino, &cactus);
    dino.yVel = 1;
    cactus.dx = -2;
    cactus.x = 320;
    oldDinoY = dino.y;
    oldCactusX = cactus.x;

    onClockTick(&model);

    assert(dino.y != oldDinoY);
    assert(cactus.x == oldCactusX - 2);
}

static void tstCollision(void)
{
    GameMdl model;
    Dino dino;
    Cactus cactus;

    initTestModel(&model, &dino, &cactus);
    cactus.x = dino.x;
    cactus.y = dino.y;

    checkCollision(&model);
    assert((model.gameStatus & LOSS_FLG) != 0);
}

int main(void)
{
    tstJumpRequest();
    tstQuitRequest();
    tstClockTick();
    tstCollision();

    printf("\nALL TESTS PASSED! :)\n");
    return 0;
}
