/*
File Name: tst_mdl.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Manually exercises initialization and dinosaur model movement routines.
*/

#include <stdio.h>
#include <stdlib.h>
#include <osbind.h>

#include "TYPES.H"
#include "model.h"

static void testModel(void)
{
    GameMdl model;
    Dino dino;
    Cactus cactus;

    model.dino = &dino;
    model.cactus = &cactus;
    initGameMdl(&model);

    printf("model initialized: score = %lu, status = 0x%X\n", model.score, model.gameStatus);
    printf("dino initialized: x = %d, y = %d\n", dino.x, dino.y);
    printf("cactus initialized: x = %d, y = %d\n", cactus.x, cactus.y);
}

/* DINO TESTS */
static void tstDinoInitialization(void)
{
    Dino dino;

    initDino(&dino, 100, 200);

    printf("dino initialization: x = %d, y = %d, xVel = %d, " "yVel = %d, isDead = %d\n", dino.x, dino.y, dino.xVel, dino.yVel, dino.isDead);
}

static void tstDinoJump(void)
{
    Dino dino;

    initDino(&dino, DINO_X_POS, DINO_Y_POS);
    dino.yVel = -JUMP_Y_VELOCITY;
    moveDino(&dino);

    printf("dino jump: x = %d, y = %d, yVel = %d\n", dino.x, dino.y, dino.yVel);
}

static void tstDinoLanding(void)
{
    Dino dino;

    initDino(&dino, DINO_X_POS, DINO_Y_POS - 1);
    dino.yVel = 1;
    moveDino(&dino);

    printf("dino landing: y = %d, yVel = %d\n", dino.y, dino.yVel);
}

static void dinoTests(void)
{
    tstDinoInitialization();
    tstDinoJump();
    tstDinoLanding();
}

/* CACTUS TESTS */
static void tstCactusMove(void)
{
    Cactus cactus;

    initCactus(&cactus, 100, 200, -5);
    moveCactus(&cactus);

    printf("cactus movement: x = %d, y = %d, dy = %d\n", cactus.x, cactus.y, cactus.dy);
}

static void tstCactusWrap(void)
{
    Cactus cactus;

    initCactus(&cactus, -CACTUS_WIDTH, 200, -1);
    moveCactus(&cactus);

    printf("cactus wrap: x = %d, y = %d\n", cactus.x, cactus.y);
}

static void cactusTests(void)
{
    tstCactusMove();
    tstCactusWrap();
}

int main(void)
{
    testModel();
    dinoTests();
    cactusTests();
    printf("\nMODEL TESTS COMPLETE.\n");
    return 0;
}