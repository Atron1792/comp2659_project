/*
File Name: game.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Initializes and runs the game loop, including timing, input, updates,
rendering, and terminal game-state screens.
*/

#include "game.h"

volatile UINT32 *timer = (UINT32 *)0x462;
static UINT32 timeThen, timeNow;
static UINT32 *originalScreen;
static UINT32 *frontBuffer;
static UINT32 *backBuffer;
static UINT8 backStorage[FRAMEBUFFER_SIZE + FRAMEBUFFER_ALIGNMENT - 1];

UINT32 getTime() {
	UINT32 old_ssp, time;
	old_ssp = Super(0);
	time = *timer;
	Super(old_ssp);
	return time;
}

void initDoubleBuffer(GameMdl* model) {
	UINT32 alignedAddress;

	originalScreen = Physbase();
	frontBuffer = originalScreen;
	clearScreen(originalScreen);
	alignedAddress = ((UINT32)backStorage + FRAMEBUFFER_ALIGNMENT - (UINT32)1) & ~(FRAMEBUFFER_ALIGNMENT - (UINT32)1);
	backBuffer = (UINT32 *)alignedAddress;
	model->base = backBuffer;
	clearScreen(model->base);
}

void presentFrame(GameMdl* model) {
	UINT32 *oldFront;

	Setscreen(backBuffer, backBuffer, -1);
	while (Physbase() != backBuffer) {
	}

	oldFront = frontBuffer;
	frontBuffer = backBuffer;
	backBuffer = oldFront;
	model->base = backBuffer;
}

void restoreScreen() {
	Setscreen(originalScreen, originalScreen, -1);
	while (Physbase() != originalScreen) {
	}
}

void processInput(GameMdl *model) {
	char key = '\0';

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
}

void updateGame(GameMdl *model) {
	UINT32 elapsed;

	timeNow = getTime();
	elapsed = timeNow - timeThen;

	if (elapsed >= 1) {
		onClockTick(model);
		if (checkCollision(model)) {
			onCollision(model);
		}
		render(model);
		presentFrame(model);
		updateMusic(elapsed);
		timeThen = timeNow;
	}
}

void renderSplash(GameMdl* model) {
	/* 1 player box border */
	plotRectangle(model->base, 192, 284, BORDER_LENGTH, BORDER_WIDTH);
	clearRegion(model->base, 192 + BORDER_THICK, 284 + BORDER_THICK, BORDER_LENGTH - (BORDER_THICK << 1), BORDER_WIDTH - (BORDER_THICK << 1));
	
	/* 2 player box border */
	plotRectangle(model->base, 216, 284, 16, 72);
	clearRegion(model->base, 218, 286, 12, 68);
	
	plotString((UINT8 *)model->base, P1_OPT_X, P1_OPT_Y, "1 Player");
	plotString((UINT8 *)model->base, P2_OPT_X, P2_OPT_Y, "2 Player");
}

void renderEndScreen(GameMdl *model) {
	if (model -> gameStatus & WIN_FLG) {
		plotString((UINT8 *)model->base, 180, 280, "YOU WIN!");
	} else if (model -> gameStatus & LOSS_FLG) {
		plotString((UINT8 *)model->base, 180, 280, "GAME OVER");
		renderGround(model->base);
		renderDino(model -> dino, model -> base);
		renderCactus(model -> cactus, model -> base);
		renderScore(model -> score, model -> base);
	} else if (model -> gameStatus & QUIT_FLG) {
		plotString((UINT8 *)model->base, 180, 280, "QUIT");
		renderScore(model -> score, model -> base);
	}
}

void gameInit(GameMdl* model) {
	initGameMdl(model);
	initDoubleBuffer(model);
	disableCursor();
	render(model);
	presentFrame(model);

	/* Initialise time checking variables */
	timeNow = getTime();
	timeThen = timeNow;
	startMusic();
}

void gameLoop(GameMdl* model) {
	while (!model -> gameStatus) {
		processInput(model);
		if (!model -> gameStatus) {
			updateGame(model);
		}
	}
	stopMusic();
	clearScreen(backBuffer); /* maybe replace with render func */
	renderEndScreen(model);
	presentFrame(model);
	while (!has_input()) {
	}
	get_input();
	restoreScreen();
}

/*----- Function: main -----

 PURPOSE: Initializes the game and runs its main loop.

 INPUT: None.

 OUTPUT: Returns zero after the game exits.
*/
int main() {
	UINT32 i=0;
	GameMdl model;
	Dino dino;
	Cactus cactus;

	model.dino = &dino;
	model.cactus = &cactus;

	gameInit(&model);
	
	gameLoop(&model);
	return 0;
}
