#ifndef MODEL_H
#define MODEL_H

/* Includes */
#include <osbind.h>
#include <stdio.h>
#include <stdlib.h>
#include "TYPES.H"


/* Dino constants */
#define JUMP_Y_VELOCITY 5 /* m/s */


/* Environment Constants */
#define FLOOR_Y 200

#define DINO_X_POS 32
#define DINO_Y_POS 168

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
void dinoJump(Dino* dino);
#endif