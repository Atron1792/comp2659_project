#include <stdio.h>
#include <stdlib.h>
#include <osbind.h>
#include <assert.h>

#include "TYPES.H"
#include "model.h"

/* Local prototypes */
void tstDinoMove();


void testModel() {
    GameModel mdl;
    initModel(&mdl);
}

/* DINO TESTS */
void dinoTests() {
    tstDinoMove();
}

void tstDinoMove() {
    Dino chuck;
    int x = 0;
    int dx = 0;
    double xVel = 0.0;
    
    int y = FLOOR_Y;
    int dy = 0;
    double yVel = 5.0;
    
    initDino(&chuck, xVel, yVel, x, y, dx, dy);
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