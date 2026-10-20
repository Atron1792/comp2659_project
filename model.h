#ifndef MODEL_H
#define MODEL_H

/* Includes */
#include "TYPES.H"


/* Dino constants */
#define JUMP_Y_VELOCITY 5 /* m/s */


/* Environment Constants */
#define FLOOR_Y 200

#define GRAVITY -10.0 /* m/s */


/* Game status flags */
#define GAME_ON_FLG 0x01
#define WIN_FLG 0x02
#define LOSS_FLG 0x04
#define QUIT_FLG 0x08
#define E_FLG 0x10 /* Currently unused */
#define F_FLG 0x20 /* Currently unused */
#define F_FLG 0x40 /* Currently unused */
#define G_FLG 0x80 /* Currently unused */



/* Structs */
typedef struct {
    double xVel, yVel;
    double x, y;
    int dx, dy;
} Dino;

typedef struct {
    int x, y;
    int dx, dy;
} Cactus;

typedef struct {
	unsigned long score;
    Dino* dino;
    Cactus* cactus;
	char gameStatus;
} GameMdl;



/* Prototypes */
void initGameMdl(GameMdl* model);
void initDino(Dino* dino, double xVel, double yVel, int x, int y, int dx, int dy);
void initCactus(Cactus* cactus);

#endif