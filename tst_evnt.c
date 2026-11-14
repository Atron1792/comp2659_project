/*
File Name: tst_evnt.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Manually exercises asynchronous requests, clock ticks, and collision events.
*/

#include <osbind.h>
#include <stdio.h>

#include "asynch.h"
#include "cond.h"
#include "synch.h"

static void initTestModel(GameMdl *model, Dino *dino, Cactus *cactus)
{
    model->score = 0L;
    model->gameStatus = 0;
    model->dino = dino;
    model->cactus = cactus;
    model->base = (UINT32 *)0;

    initDino(dino, DINO_X_POS, DINO_Y_POS);
    initCactus(cactus, 320, DINO_Y_POS, 0);
}

static void tstJumpRequest(void)
{
    GameMdl model;
    Dino dino;
    Cactus cactus;

    initTestModel(&model, &dino, &cactus);

    onJumpRequest(&model);
    printf("jump request: yVel = %d\n", dino.yVel);

    dino.y = DINO_Y_POS - 1;
    dino.yVel = 0;
    onJumpRequest(&model);
    printf("airborne jump request: yVel = %d\n", dino.yVel);
}

static void tstQuitRequest(void)
{
    GameMdl model;
    Dino dino;
    Cactus cactus;

    initTestModel(&model, &dino, &cactus);

    onQuitRequest(&model);
    printf("quit request: gameStatus = 0x%X\n", model.gameStatus);
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

    printf("clock tick: dino y %d -> %d, cactus x %d -> %d\n",oldDinoY, dino.y, oldCactusX, cactus.x);
}

static void tstCollision(void)
{
    GameMdl model;
    Dino dino;
    Cactus cactus;

    initTestModel(&model, &dino, &cactus);
    cactus.x = dino.x;
    cactus.y = dino.y;

    printf("collision check: %d, gameStatus = 0x%X\n",checkCollision(&model), model.gameStatus);

    onCollision(&model);
    printf("collision event: gameStatus = 0x%X\n", model.gameStatus);
}

int main(void)
{
    tstJumpRequest();
    tstQuitRequest();
    tstClockTick();
    tstCollision();

    return 0;
}
