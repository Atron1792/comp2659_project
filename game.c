/*
File Name: game.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Initializes and runs the game loop, including timing, input, updates,
rendering, and terminal game-state screens.
*/

#include "game.h"
#include "raster.h"
#include "input.h"
#define ESC_KEY '\x1b'

volatile UINT32 *timer = (UINT32 *)0x462;
static UINT32 timeThen, timeNow;

UINT32 getTime() {
	UINT32 old_ssp, time;
	old_ssp = Super(0);
	time = *timer;
	Super(old_ssp);
	return time;
}

void gameInit(GameMdl* model) {
	initGameMdl(model);
	disableCursor();
	render(model);
	
	/* Initialise time checking variables */
	timeNow = getTime();
	timeThen = timeNow;
}

void gameLoop(GameMdl* model) {
	char key = '\0';
	
	while (!model -> gameStatus) {
		/* Process asynchronous input requests first. */
		if (has_input()) {
			key = get_input();
		}
		if (key == ' ') {
			onJumpRequest(model);
			key = '\0';
		} else if (key == ESC_KEY) {
			onQuitRequest(model);
			key = '\0';
		}
		if (model -> gameStatus) {
			break;
		}

		/* Apply clock-triggered movement updates. */
		timeNow = getTime();
		if (timeNow - timeThen >= 1) {
			clearRegion(model -> base, model -> dino -> y, model -> dino -> x, DINO_HEIGHT, DINO_WIDTH);
			clearRegion(model -> base, model -> cactus -> y, model -> cactus -> x, CACTUS_HEIGHT, CACTUS_WIDTH);
			if (onClockTick(model)) {
				model -> dino -> isDead = 1;
			}
			renderDino(model -> dino, model -> base);
			renderCactus(model -> cactus, model -> base);
			clearRegion(model -> base, 8, SCRN_W - (5 * 8) - 8, 8, 5 * 8);
			renderScore(model -> score, model -> base);
			timeThen = timeNow;
		}
	}

	/*clearScreen(model->base);*/
	if (model -> gameStatus & WIN_FLG) {
		plotString((UINT8 *)model->base, 180, 280, "YOU WIN!");
	} else if (model -> gameStatus & LOSS_FLG) {
		plotString((UINT8 *)model->base, 180, 280, "GAME OVER");
		
		clearRegion(model -> base, model -> dino -> y, model -> dino -> x, DINO_HEIGHT, DINO_WIDTH);
		renderDino(model -> dino, model -> base);
		renderCactus(model -> cactus, model -> base);
	} else if (model -> gameStatus & QUIT_FLG) {
		plotString((UINT8 *)model->base, 180, 280, "QUIT");
	}
	while (!has_input()) {
	}
	key = get_input();
}

int main() {
	GameMdl model;
	Dino dino;
	Cactus cactus;

	model.dino = &dino;
	model.cactus = &cactus;

	gameInit(&model);
	gameLoop(&model);
	return 0;
}
