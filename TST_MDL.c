#include <stdio.h>
#include <stdlib.h>
#include <osbind.h>
#include <assert.h>

#include "TYPES.H"
#include "model.h"

/* Local prototypes */
void tstDinoMove();


void testModel() {
    GameMdl mdl;
    initGameMdl(&mdl);
}

/* DINO TESTS */
void dinoTests() {
    tstDinoMove();
}

void tstDinoMove() {
    Dino chuck;
    int x = 0;
    int y = FLOOR_Y;
    
    initDino(&chuck, x, y);
    moveDino(&chuck);
    moveDino(&chuck);
    printf("x = %d\ny = %d\n\nxVel = %lf\nyVel = %lf\n", chuck.x, chuck.y, chuck.xVel, chuck.yVel);
}


/* CACTUS TESTS */
void cactusTests() {}



int main() {
    /*testModel();*/
    dinoTests();
    printf("\nALL TESTS PASSED! :)\n");
    return 0;
}