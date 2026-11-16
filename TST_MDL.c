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

/*----- Function: testModel -----

 PURPOSE: Exercises game-model initialization with valid dinosaur and cactus
          objects.

 INPUT: None.

 OUTPUT: Prints the initialized model and sprite state.

 ASSUMPTIONS: initGameMdl() initializes the supplied sprite objects.
*/
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
/*----- Function: tstDinoInitialization -----

 PURPOSE: Displays the state produced by initializing a dinosaur.

 INPUT: None.

 OUTPUT: Prints the dinosaur's position, velocities, and death state.
*/
static void tstDinoInitialization(void)
{
    Dino dino;

    initDino(&dino, 100, 200);

    printf("dino initialization: x = %d, y = %d, xVel = %d, " "yVel = %d, isDead = %d\n", dino.x, dino.y, dino.xVel, dino.yVel, dino.isDead);
}

/*----- Function: tstDinoJump -----

 PURPOSE: Displays one dinosaur update while the dinosaur is moving upward.

 INPUT: None.

 OUTPUT: Prints the dinosaur's position and vertical velocity after movement.

 ASSUMPTIONS: The configured jump velocity and gravity are applied by
              moveDino().
*/
static void tstDinoJump(void)
{
    Dino dino;

    initDino(&dino, DINO_X_POS, DINO_Y_POS);
    dino.yVel = -JUMP_Y_VELOCITY;
    moveDino(&dino);

    printf("dino jump: x = %d, y = %d, yVel = %d\n", dino.x, dino.y, dino.yVel);
}

/*----- Function: tstDinoLanding -----

 PURPOSE: Displays the dinosaur's floor-clamping behavior during descent.

 INPUT: None.

 OUTPUT: Prints the landing position and vertical velocity.
*/
static void tstDinoLanding(void)
{
    Dino dino;

    initDino(&dino, DINO_X_POS, DINO_Y_POS - 1);
    dino.yVel = 1;
    moveDino(&dino);

    printf("dino landing: y = %d, yVel = %d\n", dino.y, dino.yVel);
}

/*----- Function: dinoTests -----

 PURPOSE: Runs the dinosaur initialization, jump, and landing demonstrations.

 INPUT: None.

 OUTPUT: Prints each dinosaur demonstration result.
*/
static void dinoTests(void)
{
    tstDinoInitialization();
    tstDinoJump();
    tstDinoLanding();
}

/* CACTUS TESTS */
/*----- Function: tstCactusMove -----

 PURPOSE: Displays one normal cactus movement update.

 INPUT: None.

 OUTPUT: Prints the cactus position and vertical displacement.
*/
static void tstCactusMove(void)
{
    Cactus cactus;

    initCactus(&cactus, 100, 200, -5);
    moveCactus(&cactus);

    printf("cactus movement: x = %d, y = %d, dy = %d\n", cactus.x, cactus.y, cactus.dy);
}

/*----- Function: tstCactusWrap -----

 PURPOSE: Displays cactus wrapping after it leaves the left side of the screen.

 INPUT: None.

 OUTPUT: Prints the wrapped cactus position.
*/
static void tstCactusWrap(void)
{
    Cactus cactus;

    initCactus(&cactus, -CACTUS_WIDTH, 200, -1);
    moveCactus(&cactus);

    printf("cactus wrap: x = %d, y = %d\n", cactus.x, cactus.y);
}

/*----- Function: cactusTests -----

 PURPOSE: Runs the normal movement and wrapping cactus demonstrations.

 INPUT: None.

 OUTPUT: Prints each cactus demonstration result.
*/
static void cactusTests(void)
{
    tstCactusMove();
    tstCactusWrap();
}

/*----- Function: main -----

 PURPOSE: Runs all model demonstrations in sequence.

 INPUT: None.

 OUTPUT: Returns zero after the demonstrations complete.
*/
int main(void)
{
    testModel();
    dinoTests();
    cactusTests();
    printf("\nMODEL TESTS COMPLETE.\n");
    return 0;
}