#include <stdio.h>
#include <stdlib.h>

#include "model.h"

void initGameMdl(GameMdl* mdl) {
	mdl -> score = 0L;
	mdl -> gameStatus = (char)GAME_ON_FLG;
    initDino(mdl -> dino, 0.0, 0.0, 0,0,0,0);
    initCactus(mdl -> cactus);
}

/*
DINO FUNCTIONS
*/
void initDino(Dino* dino, double xVel, double yVel, int x, int y, int dx, int dy) {
    dino -> x = x;
    dino -> dx = dx;
    dino -> xVel = xVel;
    
    dino -> y = y;
    dino -> dy = dy;
    dino -> yVel = yVel;
    printf("g = %lf\ndt = %lf\n", GRAVITY, (1.0/70.0));
}

void moveDino(Dino* dino) {
    double currY, newY;
    double currVel, newVel;
    
    currVel = dino -> yVel;
    newVel = currVel + ((double)GRAVITY / (1.0/70.0));

    currY = dino -> y;
    newY = newVel * (1.0/70.0) + 0.5;


    dino -> yVel = newVel;
    dino -> y = newY;
}


/*
CACTUS FUNCTIONS
*/
void initCactus(Cactus* cactus) {
    /* */
}