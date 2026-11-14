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
static UINT32 cactusThen, dinoThen, timeNow;


void gameInit(GameMdl* model) {
	initGameMdl(model);
	disableCursor();
	render(model);
	
	/* Initialise time checking variables */
	timeNow = getTime();
	cactusThen = timeNow;
	dinoThen = timeNow;
}


void initScreen(GameMdl* model) {
    model->base = Physbase();
    clearScreen(model->base);
}


void gameLoop(GameMdl* model) {
	char movements = 0;
	char key = '\0';
	
	while (!model -> gameStatus) {
		/* Handle synchronous events */
		timeNow = getTime();
		if (timeNow - cactusThen >= CACTUS_MOVE_RATE) {
			clearRegion(model -> base, model -> cactus -> y, model -> cactus -> x, CACTUS_HEIGHT, CACTUS_WIDTH);
			moveCactus(model -> cactus);
			renderCactus(model -> cactus, model -> base);
			cactusThen = timeNow;
			movements++;
		}
		if (timeNow - dinoThen >= 1) {
			clearRegion(model -> base, model -> dino -> y, model -> dino -> x, DINO_HEIGHT, DINO_WIDTH);
			moveDino(model -> dino);
			renderDino(model -> dino, model -> base);
			dinoThen = timeNow;
			movements++;
		}

		if (movements) {
			if (checkCollision(model)) {
				onCollision(model);
				model -> dino -> isDead = 1;
			}
			movements = 0;
		}
		
		if (model -> gameStatus) {
			break;
		}
		
		
		/* Poll for user input */
		if (has_input()) {
			key = get_input();
		}

		/* Process user input (if any) */
		if (key == ' ') {
			onJumpRequest(model);
			key = '\0';
		} else if (key == ESC_KEY) {
			onQuitRequest(model);
			key = '\0';
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



UINT32 getTime() {
	UINT32 old_ssp, time;
	old_ssp = Super(0);
	time = *timer;
	Super(old_ssp);
	return time;
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
