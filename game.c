#include "game.h"
#define ESC_KEY '\x1b'

volatile UINT32 *timer = (UINT32 *)0x462;
static UINT32 timeThen, timeNow;


void gameInit(GameMdl* model) {
	disableCursor();
	initGameMdl(model);
}


void initScreen(GameMdl* model) {
	/* IMPLEMENT ME */
}


void gameLoop(GameMdl* model) {
	char key = '\0';
	
	while (model -> gameStatus & GAME_ON_FLG) {
		if (Cconis()) {
			key = (char)Cnecin();
		}

		if (key == ' ') {
			/*  */
			onJumpRequest(model);
			key = '\0';
		} else if (key == ESC) {
			/*  */
			onQuitRequest(model);
			key = '\0';
		}
	}

	if (model -> gameStatus & WIN_FLG) {
		/*  */
	} else if (model -> gameStatus & LOSS_FLG) {
		/*  */
	} else if (model -> gameStatus & QUIT_FLG) {
		/*  */
	} else {}
}



UINT32 getTime() {
	UINT32 old_ssp, time;
	old_ssp = Super(0);
	time = *timer;
	Super(old_ssp);
	return time;
}


int main() {
	return 0;
}
