/*
File Name: renderer.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Composes the game scene, sprites, ground line, and score on the framebuffer.
*/

#include "renderer.h"
#include "model.h"

void renderMenuButton(UINT32 *base, int row, char *label, int labelCol, int selected)
{
    if (selected)  {
        plotRectangle(base, row - 3, MENU_BUTTON_COL - 3, MENU_BUTTON_HEIGHT + 6, MENU_BUTTON_WIDTH + 6);
    }

    plotRectangle(base, row, MENU_BUTTON_COL, MENU_BUTTON_HEIGHT, MENU_BUTTON_WIDTH);
    clearRegion(base, row + MENU_BORDER_THICK, MENU_BUTTON_COL + MENU_BORDER_THICK,
        MENU_BUTTON_HEIGHT - (MENU_BORDER_THICK << 1),
        MENU_BUTTON_WIDTH - (MENU_BORDER_THICK << 1));
    plotString(base, row + 19, labelCol, label);
}

void renderSplashScreen(UINT32 *base, int selectedOption)
{
    int i;
    int secondButtonRow;
    int thirdButtonRow;
    UINT8 *screen;

    secondButtonRow = MENU_BUTTON_ROW + MENU_BUTTON_HEIGHT + MENU_BUTTON_GAP;
    thirdButtonRow = secondButtonRow + MENU_BUTTON_HEIGHT + MENU_BUTTON_GAP;
    screen = (UINT8 *)base;
    for (i = 0; i < SCREEN_HEIGHT * BYTES_PER_SCANLINE; i++) {
        screen[i] = splashBitmap[i];
    }
    renderMenuButton(base, MENU_BUTTON_ROW, "1 PLAYER", 288, selectedOption == 0);
    renderMenuButton(base, secondButtonRow, "2 PLAYER", 288, selectedOption == 1);
    renderMenuButton(base, thirdButtonRow, "QUIT", 304, selectedOption == 2);
    plotString(base, 330, 236, "2 PLAYER COMING SOON");
    plotString(base, 352, 180, "TAB SELECT  ENTER CHOOSE  ESC QUIT");
}

void renderGame(const GameMdl *model)
{
    clearScreen(model->base);
    renderGround(model->base);
    clearRegion(model->base, model->dino->y, model->dino->x, DINO_HEIGHT, DINO_WIDTH);
    clearRegion(model->base, model->cactus->y, model->cactus->x, CACTUS_HEIGHT, CACTUS_WIDTH);
    renderDino(model->dino, model->base);
    renderCactus(model->cactus, model->base);
    clearRegion(model->base, 8, SCRN_W - (5 * 8) - 8, 8, 5 * 8);
    renderScore(model->score, model->base);
}

void renderGround(UINT32 *base)
{
    plotHorizontalLine(base, FLOOR_Y, 0, SCRN_W);
}

void renderDino(const Dino *dino, UINT32 *base)
{
    const UINT32 *bitmap;

    if (dino -> isDead) {
        bitmap = dinoBitmapDeath;
    } else if (dino->yVel < 0) {
        bitmap = dinoBitmap2;
    } else if (dino->yVel > 0) {
        bitmap = dinoBitmap1;
    } else {
        bitmap = dinoBitmap0;
    }

    plot32bitBitmap(base, dino->y, dino->x, bitmap, DINO_HEIGHT);
}

void renderCactus(const Cactus *cactus, UINT32 *base) {
    int i;
    for (i = 0; i < NUMBER_OF_CACTI; i++) {
        plot32bitBitmap(base, cactus->y, cactus->x + (i * CACTUS_SEPARATION), cactusBitmap, CACTUS_HEIGHT);
    }
}

void renderScore(UINT32 score, UINT32* base) {
    char scoreText[6];
    int i;

    scoreText[5] = '\0';
    for (i = 4; i >= 0; i--) {
        scoreText[i] = (char)('0' + (score % 10));
        score /= 10;
    }

    plotString(base, 8, SCRN_W - (5 * 8) - 8, scoreText);
}

void disableCursor() {
	printf("\033f");
	fflush(stdout);
}
