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

/*----- Function: initTestModel -----

 PURPOSE: Creates a deterministic model fixture for event tests.

 INPUT: model(GameMdl *) - Model to configure.
        dino(Dino *) - Dinosaur fixture object.
        cactus(Cactus *) - Cactus fixture object.

 OUTPUT: None

 ASSUMPTIONS: model, dino, and cactus point to writable test state.
*/
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

/*----- Function: tstJumpRequest -----

 PURPOSE: Demonstrates grounded and airborne jump requests.

 INPUT: None.

 OUTPUT: None - Prints the vertical velocity after each request.

 ASSUMPTIONS: The dinosaur is tested once on the floor and once airborne.
*/
static void tstJumpRequest()
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

/*----- Function: tstQuitRequest -----

 PURPOSE: Demonstrates setting the quit status through an asynchronous request.

 INPUT: None.

 OUTPUT: None - Prints the resulting game status.

 ASSUMPTIONS: The fixture model starts with no status flags set.
*/
static void tstQuitRequest()
{
    GameMdl model;
    Dino dino;
    Cactus cactus;

    initTestModel(&model, &dino, &cactus);

    onQuitRequest(&model);
    printf("quit request: gameStatus = 0x%X\n", model.gameStatus);
}

/*----- Function: tstClockTick -----

 PURPOSE: Demonstrates one synchronous movement and scoring update.

 INPUT: None.

 OUTPUT: None - Prints positions before and after the clock tick.

 ASSUMPTIONS: The fixture dinosaur and cactus have one tick of movement.
*/
static void tstClockTick()
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

/*----- Function: tstCollision -----

 PURPOSE: Demonstrates collision detection and loss-status handling.

 INPUT: None.

 OUTPUT: None - Prints collision and status results.

 ASSUMPTIONS: The sprites are positioned to overlap before the collision test.
*/
static void tstCollision()
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

/*----- Function: main -----

 PURPOSE: Runs all asynchronous, synchronous, and collision demonstrations.

 INPUT: None.

 OUTPUT: int - Zero after all demonstrations complete.
*/
int main()
{
    tstJumpRequest();
    tstQuitRequest();
    tstClockTick();
    tstCollision();

    return 0;
}
