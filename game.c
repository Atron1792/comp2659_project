#include "game.h"


void initScreen(GameModel* model) {
    /* IMPLEMENT ME */
}


void gameLoop(GameModel* model) {
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