#include "model.h"

void initGameMdl(GameMdl* mdl) {
	mdl -> score = 0L;
	mdl -> gameStatus = 0x00 | (char)(GAME_ON_FLG);
    
    initDino(mdl -> dino, 0, 0, DINO_X_POS, DINO_Y_POS, 0, 0, 0);
    initCactus(mdl -> cactus, 0,0,0,0);
    
    mdl -> base = (UINT16*)Physbase();
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
    cactus -> y += cactus -> dy; /*we can remove this catus not changing y*/
}


int checkIntersect(Dino* dino, Cactus* cactus) {
    int dbrxp, cx, dy; /*dino bottem right x-axius pixel*/
    dbrxp = DINO_X_POS;
    dbrxp += 15;
    cx = cactus -> x;
    if (dbrxp > cx) { /*if catus could possibly have its x interspt in dinos*/
        dy = dino -> y;
        dy -= 15; /*we do this to find lowest pixel of dinos y*/
        if (cactus -> y > dy) { /*dinos and catus y axus intersects.*/
            cx += 15;
            if (cx > DINO_X_POS) { /*if upper right most pixel isn't farther than dino */
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

void dinoJump(Dino* dino) {
    if (dino -> y == DINO_Y_POS) { /* sets up start of dino jump(dino on ground) */
        dino -> yVel = 2;
        dino -> counter = 0;
    }
    dino -> y += dino -> yVel;
    dino -> counter += 1;
    if (dino -> counter == 16) { /*for changeing yvel accounting for acceleration.*/
        dino -> yVel += dino -> a;
        dino -> counter = 0;
        
        /*
        if (dino -> yVel == 0) {
            dino -> counter = 10;
        }
        */
    }
}