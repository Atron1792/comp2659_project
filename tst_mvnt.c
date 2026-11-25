/*
File Name: tst_mvnt.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Demonstrates dinosaur jumping, cactus movement, rendering, and collision.
*/

#include <osbind.h>
#include <stdio.h>

#include "bitmaps.h"
#include "asynch.h"
#include "cond.h"
#include "model.h"
#include "raster.h"
#include "renderer.h"

/*----- Function: initMovementModel -----

 PURPOSE: Connects test-owned sprites to a model and initializes their state.

 INPUT: model(GameMdl *) - Model to configure.
        dino(Dino *) - Dinosaur object to initialize.
        cactus(Cactus *) - Cactus object to initialize.

 OUTPUT: None

 ASSUMPTIONS: model, dino, and cactus point to writable test state.
*/
static void initMovementModel(GameMdl *model, Dino *dino, Cactus *cactus)
{
    model->score = 0L;
    model->gameStatus = 0;
    model->dino = dino;
    model->cactus = cactus;
    model->base = Physbase();

    initDino(dino, DINO_X_POS, DINO_Y_POS);
    initCactus(cactus, 640 - CACTUS_WIDTH, FLOOR_Y - CACTUS_HEIGHT, -4);
}

/*----- Function: main -----

 PURPOSE: Demonstrates movement, rendering, and collision handling.

 INPUT: None

 OUTPUT: int - Zero after the movement demonstration completes.

 ASSUMPTIONS: The physical framebuffer is valid.
*/
int main()
{
    int counter;
    GameMdl model;
    Dino dino;
    Cactus cactus;

    initMovementModel(&model, &dino, &cactus);
    for (counter = 0; counter < 160; counter++) {
        onJumpRequest(&model);
        moveDino(model.dino);
        moveCactus(model.cactus);

        clearScreen(model.base);
        renderDino(model.dino, model.base);
        renderCactus(model.cactus, model.base);
    }

    cactus.x = dino.x;
    cactus.y = dino.y;
    printf("collision check: %d\n", checkCollision(&model));
    onCollision(&model);
    printf("game status after collision: 0x%X\n", model.gameStatus);

    return 0;
}
