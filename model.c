#include "model.h"

void initModel(GameModel* mdl) {
	mdl -> score = 0L;
	mdl -> gameStatus = (char)(GAME_ON_FLG);
    
    initDino(mdl -> dino, 0, 0, DINO_X_POS, DINO_Y_POS, 0,0);
    initCactus(mdl -> cactus, 0,0,0,0);
    
    mdl -> base = (UINT16*)Physbase();
}

/*
DINO FUNCTIONS
*/
void initDino(Dino* dino, int xVel, int yVel, int x, int y, int dx, int dy) {
    /* This function is still being developed */
    dino -> x = x;
    dino -> dx = dx;
    dino -> xVel = xVel;
    
    dino -> y = y;
    dino -> dy = dy;
    dino -> yVel = yVel;
}

void moveDino(Dino* dino) {
    int currY, newY;
    int currVel, newVel;
    
    currVel = dino -> yVel;
    newVel = currVel + ((int)GRAVITY / (1.0/35.0));

    currY = dino -> y;
    newY = newVel * (1.0/35.0);


    dino -> yVel = newVel;
    dino -> y = newY;
}


/*
CACTUS FUNCTIONS
*/
void initCactus(Cactus* cactus, int x, int y, int dx, int dy) {
    cactus -> x = x;
    cactus -> y = y;
    cactus -> dx = dx;
    cactus -> dy = dy;
}

void moveCactus(Cactus* cactus) {
    cactus -> x += cactus -> dx;
    cactus -> y += cactus -> dy;
}


