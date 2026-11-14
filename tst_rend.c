/*
file name: tst_rend.c
authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Exercises complete scene rendering using initialized game-model objects.
*/

#include <osbind.h>

#include "TYPES.H"
#include "model.h"
#include "renderer.h"

int main(void)
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