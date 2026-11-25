/*
File Name: model.h
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Declares game-state structures, constants, initialization, and movement logic.
*/

#ifndef MODEL_H
#define MODEL_H

/* Includes */
#include <osbind.h>
#include <stdio.h>
#include <stdlib.h>
#include "TYPES.H"
#include "bitmaps.h"


/* Dino constants */
#define JUMP_Y_VELOCITY 10 /* frames */

#define DINO_X_POS 32
#define DINO_Y_POS (FLOOR_Y - DINO_HEIGHT)


/* Cactus constants */
#define DX_CACTUS -5
#define DY_CACTUS 0
#define CACTUS_MOVE_RATE 2 /* frames */
#define NUMBER_OF_CACTI 1
#define CACTUS_SEPARATION (SCRN_W / NUMBER_OF_CACTI)

/* Environment Constants */
#define SCRN_W 640
#define SCRN_H 400

#define FLOOR_Y (SCRN_H - DINO_HEIGHT)

#define GRAVITY -1


/* Game status flags */
#define WIN_FLG 0x01
#define LOSS_FLG 0x02
#define QUIT_FLG 0x04
#define D_FLG 0x08 /* Unused flag */
#define E_FLG 0x10 /* Unused flag */
#define F_FLG 0x20 /* Unused flag */
#define G_FLG 0x40 /* Unused flag */
#define H_FLG 0x80 /* Unused flag */


/* Structs */
typedef struct {
    int xVel, yVel;
    int x, y;
    char isDead;
} Dino;

typedef struct {
    int x, y;
    int dx, dy;
} Cactus;

typedef struct {
	UINT32 score;
    Dino* dino;
    Cactus* cactus;
    UINT32* base;
	char gameStatus;
} GameMdl;



/* Prototypes */
/*----- Function: initGameMdl -----

 PURPOSE: Initializes scalar game state and any supplied sprite objects.

 INPUT: model(GameMdl *) - Game model to initialize; its sprite pointers may be null.

 OUTPUT: None

 ASSUMPTIONS: model points to writable game state.
*/
void initGameMdl(GameMdl* model);

/*----- Function: initDino -----

 PURPOSE: Initializes a dinosaur's position, velocity, and animation state.

 INPUT: dino(Dino *) - Dinosaur to initialize.
        x(int) - Initial horizontal coordinate.
        y(int) - Initial vertical coordinate.

 OUTPUT: None

 ASSUMPTIONS: dino points to writable dinosaur state.
*/
void initDino(Dino* dino, int x, int y);

/*----- Function: moveDino -----

 PURPOSE: Advances dinosaur position, gravity, and floor clamping by one tick.

 INPUT: dino(Dino *) - Dinosaur state to update.

 OUTPUT: None

 ASSUMPTIONS: A negative y velocity moves upward and GRAVITY is negative.
*/
void moveDino(Dino* dino);

/*----- Function: initCactus -----

 PURPOSE: Initializes a cactus's position and horizontal velocity.

 INPUT: cactus(Cactus *) - Cactus to initialize.
        x(int) - Initial horizontal coordinate.
        y(int) - Initial vertical coordinate.
        dx(int) - Horizontal displacement per update.

 OUTPUT: None

 ASSUMPTIONS: cactus points to writable cactus state.
*/
void initCactus(Cactus* cactus, int x, int y, int dx);

/*----- Function: moveCactus -----

 PURPOSE: Advances a cactus and wraps it to the right edge after leaving screen. Or in the case of multiple cacti, moves the cactus to the right of the last one.

 INPUT: cactus(Cactus *) - Cactus state to update.

 OUTPUT: None

 ASSUMPTIONS: The left edge wrap condition assumes a positive rightward position; horizontal wrapping is updated from cactus->dx.
*/
void moveCactus(Cactus* cactus);

#endif