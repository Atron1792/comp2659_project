#include "renderer.h"


void render(const GameMdl *model)
{
    clearScreen(model->base);
    
    renderGround(model);
    renderDino(model->dino, model->base);
    renderCactus(model->cactus, model->base);
}

void renderGround(const GameMdl *model)
{
    plotHorizontalLine(model->base, FLOOR_Y, 0, SCRN_W);
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
