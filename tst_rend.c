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
    render(&mdl, base);
    return 0;
}