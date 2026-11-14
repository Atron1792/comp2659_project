#include "renderer.h"

#include "raster.h"
#include "bitmaps.h"
#include "TYPES.H"
#include "model.h"

void render(const GameMdl *model)
{
    clearScreen(model->base);
    
    renderDino(model->dino, model->base);
    renderCactus(model->cactus, model->base);
}

void renderDino(const Dino *dino, UINT32 *base)
{
    const UINT32 *bitmap;

    if (dino->yVel < 0) {
        bitmap = dinoBitmap2;
    } else if (dino->yVel > 0) {
        bitmap = dinoBitmap1;
    } else {
        bitmap = dinoBitmap0;
    }

    plot32bitBitmap(base, dino->y, dino->x, bitmap, DINO_HEIGHT);
}

void renderCactus(const Cactus *cactus, UINT32 *base)
{
    plot32bitBitmap(base, cactus->y, cactus->x, cactusBitmap, CACTUS_HEIGHT);
}


void renderScore(UINT32 score, UINT32* base) {
    /* IMPLEMENT ME */
}


void disableCursor() {
	printf("\033f");
	fflush(stdout);
}
