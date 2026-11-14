#include "model.h"
#include "bitmaps.h"

void initGameMdl(GameMdl* mdl) {
	mdl -> score = 0L;
	mdl -> gameStatus = 0;
    
    initDino(mdl -> dino, DINO_X_POS, DINO_Y_POS);
    initCactus(mdl -> cactus, 0, 0, 0);
    
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
    dino -> dx = 0;
    dino -> dy = 0;
    dino -> a = 0;
    dino -> counter = 0;
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

void dinoJump(Dino* dino) {
    if (dino -> y >= DINO_Y_POS && dino -> yVel >= 0) {
        dino -> y = DINO_Y_POS;
        dino -> yVel = -JUMP_Y_VELOCITY;
    }

    dino -> y += dino -> yVel;
    dino -> yVel += 1;

    if (dino -> y >= DINO_Y_POS) {
        dino -> y = DINO_Y_POS;
        dino -> yVel = 0;
    }
}


/*
CACTUS FUNCTIONS
*/
void initCactus(Cactus* cactus, int x, int y, int dx) {
    cactus -> x = x;
    cactus -> y = y;
    cactus -> dx = dx;
    cactus -> dy = 0;
}

void moveCactus(Cactus* cactus) {
    cactus -> x += cactus -> dx;
}


int checkIntersect(const Dino* dino, const Cactus* cactus) {
    return (dino->x < cactus->x + CACTUS_WIDTH &&
           dino->x + DINO_WIDTH > cactus->x) &&
           (dino->y < cactus->y + CACTUS_HEIGHT &&
           dino->y + DINO_HEIGHT > cactus->y);
}
