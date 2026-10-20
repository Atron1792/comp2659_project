#include "asynch.h"

/*void on_jump_request(GameMdl *model)*/

void on_quit_request(GameMdl *model)
{
    model->gameStatus |= QUIT_FLG;
}