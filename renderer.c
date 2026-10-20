#include "renderer.h"

#include "raster.h"
#include "bitmaps.h"
#include "types.h"
#include "model.h"

void render(const GameMdl *model, UINT32 *base)
{
    clear_screen(base);
    renderDino(model->dino, (UINT16 *)base);

    renderCactus(model->cactus, (UINT16 *)base);
}

void renderDino(const Dino *dino, UINT16 *base)
{
    plot_16bit_bitmap(base, dino->x, dino->y, dinoBitmap, 16);
}

void renderCactus(const Cactus *cactus, UINT16 *base)
{
    plot_16bit_bitmap(base, cactus->x, cactus->y, cactusBitmap, 16);
}