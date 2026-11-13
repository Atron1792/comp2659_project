#include "renderer.h"

#include "raster.h"
#include "bitmaps.h"
#include "TYPES.H"
#include "model.h"

void render(const GameMdl *model, UINT32 *base)
{
    clearScreen(base);
    renderDino(model->dino, (UINT16 *)base);

    renderCactus(model->cactus, (UINT16 *)base);
}

void renderDino(const Dino *dino, UINT16 *base)
{
    const UINT16 *bitmap;

    if (dino->yVel < 0) {
        bitmap = dinoBitmap2;
    } else if (dino->yVel > 0) {
        bitmap = dinoBitmap1;
    } else {
        bitmap = dinoBitmap0;
    }

    plot16bitBitmap(base, dino->y, dino->x, bitmap, HEIGHT_DINO);
}

void renderCactus(const Cactus *cactus, UINT16 *base)
{
    plot16bitBitmap(base, cactus->y, cactus->x, cactusBitmap, HEIGHT_CACTUS);
}