#include "TYPES.H"
#include <osbind.h>
#include "model.h"
#include "asynch.h"
#include "synch.h"
#include "cond.h"
#include "bitmaps.h"
#include "raster.h"
#include "renderer.h"

int main(void)
{
    int counter;
    GameMdl mdl;
    Dino dimbo;
    Cactus cactus;
    UINT32 *base;

    base = Physbase();
    mdl.dino = &dimbo;
    mdl.cactus = &cactus;

    initGameMdl(&mdl);
    
    for (counter = 0; counter < 80; counter++) {
        dinoJump(mdl->dino);
        renderDino(mdl->dino, (UINT16 *)mdl->base);
        
    }
}