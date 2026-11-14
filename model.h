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
#define JUMP_Y_VELOCITY 10 /* m/s */


/* Cactus constants */
#define DX_CACTUS -2
#define DY_CACTUS 0
#define CACTUS_MOVE_RATE 2 /* frames */

/* Environment Constants */
#define SCRN_W 640
#define SCRN_H 400

#define FLOOR_Y (SCRN_H - DINO_HEIGHT)

#define DINO_X_POS 32
#define DINO_Y_POS (FLOOR_Y - DINO_HEIGHT)

#define GRAVITY -1


/* Game status flags */
#define WIN_FLG 0x01
#define LOSS_FLG 0x02
#define QUIT_FLG 0x04
#define D_FLG 0x80 /* Unused flag */
#define E_FLG 0x10 /* Unused flag */
#define F_FLG 0x20 /* Unused flag */
#define G_FLG 0x40 /* Unused flag */
#define H_FLG 0x80 /* Unused flag */


/* Structs */
typedef struct {
    int xVel, yVel;
    int x, y;
    int dx, dy;
    int a;
    int counter;
    char isDead;
} Dino;

typedef struct {
    int x, y;
    int dx, dy;
} Cactus;

typedef struct {
	unsigned long score;
    Dino* dino;
    Cactus* cactus;
    UINT32* base;
	char gameStatus;
} GameMdl;



/* Prototypes */
/*----- Function: initGameMdl -----

 PURPOSE: Initializes scalar game state and any supplied sprite objects.

 INPUT: model - game model to initialize; its sprite pointers may be null.

 OUTPUT: None.

 ASSUMPTIONS: The framebuffer returned by Physbase is valid.
*/
void initGameMdl(GameMdl* model);

/*----- Function: initDino -----

 PURPOSE: Initializes a dinosaur's position, velocity, and animation state.

 INPUT: dino - dinosaur to initialize; x and y - starting coordinates.

 OUTPUT: None.
*/
void initDino(Dino* dino, int x, int y);

/*----- Function: moveDino -----

 PURPOSE: Advances dinosaur position, gravity, and floor clamping by one tick.

 INPUT: dino - dinosaur state to update.

 OUTPUT: None.

 ASSUMPTIONS: A negative y velocity moves upward and GRAVITY is negative.
*/
void moveDino(Dino* dino);

/*----- Function: initCactus -----

 PURPOSE: Initializes a cactus's position and horizontal velocity.

 INPUT: cactus - cactus to initialize; x and y - starting coordinates;
        dx - horizontal movement per update.

 OUTPUT: None.
*/
void initCactus(Cactus* cactus, int x, int y, int dx);

/*----- Function: moveCactus -----

 PURPOSE: Advances a cactus and wraps it to the right edge after leaving screen.

 INPUT: cactus - cactus state to update.

 OUTPUT: None.
*/
void moveCactus(Cactus* cactus);

/*----- Function: checkIntersect -----

 PURPOSE: Tests whether the dinosaur and cactus rectangles overlap.

 INPUT: dino - dinosaur bounds; cactus - cactus bounds.

 OUTPUT: Nonzero for overlap, zero otherwise.

 ASSUMPTIONS: Sprite dimensions are DINO_WIDTH/HEIGHT and CACTUS_WIDTH/HEIGHT.
*/
int checkIntersect(const Dino* dino, const Cactus* cactus);
#endif