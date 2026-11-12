#include "game.h"


void initScreen(GameMdl* model) {
    /* IMPLEMENT ME */
}


void gameLoop(GameMdl* model) {
    while (model -> gameStatus & GAME_ON_FLG) {
        /**/
    }

    if (model -> gameStatus & WIN_FLG) {
        /*  */
    } else if (model -> gameStatus & LOSS_FLG) {
        /*  */
    } else if (model -> gameStatus & QUIT_FLG) {
        /*  */
    } else {}
}

int main() {
    return 0;
}