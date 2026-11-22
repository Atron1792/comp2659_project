/*
File Name: model.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Initializes and updates the dinosaur, cactus, and overall game model state.
*/

#include "model.h"
#include "bitmaps.h"

void initGameMdl(GameMdl* mdl) {
	mdl -> score = 0L;
	mdl -> gameStatus = 0;

    if (mdl->dino) {
        initDino(mdl -> dino, DINO_X_POS, DINO_Y_POS);
    }
    if (mdl->cactus) {
        initCactus(mdl -> cactus, SCRN_W - CACTUS_WIDTH, FLOOR_Y - CACTUS_HEIGHT, DX_CACTUS);
    }

    mdl -> base = Physbase();
}

/*
DINO FUNCTIONS
*/
void initDino(Dino* dino, int x, int y) {
    dino -> xVel = 0;
    dino -> yVel = 0;
    dino -> x = x;
    dino -> y = y;
    dino -> isDead = 0;
}

void moveDino(Dino* dino) {
    if (dino->y >= DINO_Y_POS && dino->yVel >= 0) {
        dino->yVel = 0;
        dino->y = DINO_Y_POS;
        return;
    }

    dino->y += dino->yVel;
    dino->yVel -= GRAVITY;

    if (dino->y >= DINO_Y_POS) {
        dino->y = DINO_Y_POS;
        dino->yVel = 0;
    }
}

/*
CACTUS FUNCTIONS
*/
void initCactus(Cactus* cactus, int x, int y, int dx) {
    int i;
    cactus -> y = y;
    cactus -> dx = dx;
    cactus -> dy = 0;
    for (i = 0; i < 3; i++) {
        cactus -> ca[i] = 200 + (i * 202);
    }
    cactus -> x = cactus -> ca[0];
}

void moveCactus(Cactus* cactus) {
    int i;
    for (i = 0; i < 3; i++) {
        cactus -> ca[i] += cactus -> dx;
    }
    if (cactus -> ca[0] < 0) {
        cactus -> ca[0] = cactus -> ca[1];
        cactus -> ca[1] = cactus -> ca[2];
        cactus -> ca[2] = 608;
    }
    cactus -> x = cactus -> ca[0];
}


int checkIntersect(const Dino* dino, const Cactus* cactus) {
    return (dino->x < cactus->x + CACTUS_WIDTH &&
           dino->x + DINO_WIDTH > cactus->x) &&
           (dino->y < cactus->y + CACTUS_HEIGHT &&
           dino->y + DINO_HEIGHT > cactus->y);
}
