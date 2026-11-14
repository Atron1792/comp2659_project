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
void initGameMdl(GameMdl* model);

void initDino(Dino* dino, int x, int y);
void moveDino(Dino* dino);

void initCactus(Cactus* cactus, int x, int y, int dx);
void moveCactus(Cactus* cactus);


int checkIntersect(const Dino* dino, const Cactus* cactus);
#endif