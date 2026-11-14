#include "game.h"
#include "raster.h"
#define ESC_KEY '\x1b'

volatile UINT32 *timer = (UINT32 *)0x462;
static UINT32 timeThen, timeNow;


void gameInit(GameMdl* model) {
	disableCursor();
	initGameMdl(model);
	
	/* Initialise time checking variables */
	timeThen = getTime();
	timeNow = timeThen;
}


void initScreen(GameMdl* model) {
    model->base = Physbase();
    clearScreen(model->base);
}


void gameLoop(GameMdl* model) {
	UINT32 timeDiff;
	char key = '\0';
	
	while (!model -> gameStatus) {
		/* Handle synchronous events */
		timeNow = getTime();
		timeDiff = timeThen - timeNow;
		if (timeDiff >= CACTUS_MOVE_RATE) {
			moveCactus(model->cactus);
		}
		if (timeDiff >= 1) {
			onJumpRequest(model);
		}
		
		
		/* Poll for user input */
		if (Cconis()) {
			key = (char)Cnecin();
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

	clearScreen(model->base);
	if (model -> gameStatus & WIN_FLG) {
		plotString((UINT8 *)model->base, 180, 280, "YOU WIN");
	} else if (model -> gameStatus & LOSS_FLG) {
		plotString((UINT8 *)model->base, 180, 280, "GAME OVER");
	} else if (model -> gameStatus & QUIT_FLG) {
		plotString((UINT8 *)model->base, 180, 280, "QUIT");
	}
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

	gameLoop(&model);
	return 0;
}
