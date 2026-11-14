#include "model.h"
#include "bitmaps.h"

void initGameMdl(GameMdl* mdl) {
	mdl -> score = 0L;
	mdl -> gameStatus = 0x00 | (char)(GAME_ON_FLG);
    
    initDino(mdl -> dino, 0, 0, DINO_X_POS, DINO_Y_POS, 0, 0, 0);
    initCactus(mdl -> cactus, 0,0,0,0);
    
    mdl -> base = Physbase();
}

/*
DINO FUNCTIONS
*/
void initDino(Dino* dino, int xVel, int yVel, int x, int y, int dx, int dy, int a) {
    /* This function is still being developed */
    dino -> x = x;
    dino -> dx = dx;
    dino -> xVel = xVel;
    
    dino -> y = y;
    dino -> dy = dy;
    dino -> yVel = yVel;
    dino -> a = a;
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
}


int checkIntersect(const Dino* dino, const Cactus* cactus) {
    return (dino->x < cactus->x + CACTUS_WIDTH &&
           dino->x + DINO_WIDTH > cactus->x) &&
           (dino->y < cactus->y + CACTUS_HEIGHT &&
           dino->y + DINO_HEIGHT > cactus->y);
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