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

	originalScreen = get_video_base();
	frontBuffer = originalScreen;
	clearScreen(originalScreen);
	alignedAddress = ((UINT32)backStorage + FRAMEBUFFER_ALIGNMENT - 1) & ~(FRAMEBUFFER_ALIGNMENT - 1);
	backBuffer = (UINT32 *)alignedAddress;
	model->base = backBuffer;
	clearScreen(model->base);
}

void presentFrame(GameMdl* model) {
	UINT32 *oldFront;

	set_video_base(backBuffer);
	while (get_video_base() != backBuffer) {
	}

	oldFront = frontBuffer;
	frontBuffer = backBuffer;
	backBuffer = oldFront;
	model->base = backBuffer;
}

void restoreScreen() {
	set_video_base(originalScreen);
	while (get_video_base() != originalScreen) {
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
	timeThen = timeNow;

	updateMusic(elapsed);

	if (elapsed >= 1) {
		onClockTick(model);
		if (checkCollision(model)) {
			onCollision(model);
		}
		renderGame(model);
		presentFrame(model);
	}
}

int gameSplashScreen(GameMdl* model) {
	int selectedOption;
	int key;

	selectedOption = 0;
	renderSplashScreen(model->base, selectedOption);
	presentFrame(model);

	while (1) {
		if (!has_input()) {
			continue;
		}

		key = get_input();
		if (key == '\t')
		{
			selectedOption = (selectedOption + 1) % MENU_OPTION_COUNT;
			renderSplashScreen(model->base, selectedOption);
			presentFrame(model);
		} else if (key == ESC_KEY) 
		{
			return 0;
		} else if ((key == '\r' || key == '\n') && selectedOption == 0) 
		{
			return 1;
		} else if ((key == '\r' || key == '\n') && selectedOption == 2) 
		{
			return 0;
		}
	}
}

void renderEndScreen(GameMdl *model) {
	if (model -> gameStatus & WIN_FLG) {
		plotString(model->base, 180, 280, "YOU WIN!");
	} else if (model -> gameStatus & LOSS_FLG) {
		plotString(model->base, 180, 280, "GAME OVER");
		renderGround(model->base);
		renderDino(model -> dino, model -> base);
		renderCactus(model -> cactus, model -> base);
		renderScore(model -> score, model -> base);
	} else if (model -> gameStatus & QUIT_FLG) {
		plotString(model->base, 180, 280, "QUIT");
		renderScore(model -> score, model -> base);
	}
	plotString(model->base, 352, 224, "PRESS ANY KEY FOR MENU");
}

void gameInit(GameMdl* model) {
	initGameMdl(model);
	model->base = backBuffer;
	disableCursor();
	renderGame(model);
	presentFrame(model);

	/* Initialise time checking variables */
	timeNow = getTime();
	timeThen = timeNow;
	startMusic();
}

void gameLoop(GameMdl* model) {
	gameInit(model);
	while (!model -> gameStatus) {
		processInput(model);
		if (!model -> gameStatus) 
		{
			updateGame(model);
		}
	}
	stopMusic();
	clearScreen(backBuffer); /* maybe replace with render func */
	renderEndScreen(model);
	presentFrame(model);
	while (!has_input()) {}
	get_input();
}

/*----- Function: main -----

 PURPOSE: Initializes the game and runs its main loop.

 INPUT: None.

 OUTPUT: Returns zero after the game exits.
*/
int main() {
	int playerMode;
	GameMdl model;
	Dino dino;
	Cactus cactus;

	model.dino = &dino;
	model.cactus = &cactus;

	initDoubleBuffer(&model);
	disableCursor();
	while (1) {
		playerMode = gameSplashScreen(&model);
		if (playerMode != 1) {
			break;
		}
		gameLoop(&model);
	}
	restoreScreen();
	return 0;
}
