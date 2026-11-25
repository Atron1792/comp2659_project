/*
File Name: tst_rend.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Exercises complete scene rendering using initialized game-model objects.
*/

#include <osbind.h>

#include "TYPES.H"
#include "model.h"
#include "renderer.h"

/*----- Function: main -----

 PURPOSE: Renders one initialized game scene to the physical framebuffer.

 INPUT: None

 OUTPUT: int - Zero after the scene is rendered.

 ASSUMPTIONS: The physical framebuffer is valid and both sprites are initialized.
*/
int main()
{
    GameMdl mdl;
    Dino dino;
    Cactus cactus;
    UINT32 *base;

    base = Physbase();
    mdl.dino = &dino;
    mdl.cactus = &cactus;

    initGameMdl(&mdl);
    render(&mdl);
    return 0;
}