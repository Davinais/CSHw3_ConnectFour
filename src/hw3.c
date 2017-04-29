#include <stdio.h>
#include "board.h"

int main(int argc, char** argv)
{
    Game game;
    initBoard(&game);
    if(argc == 2)
    {
        readBoard(&game, argv[1]);
    }
    printBoard(&game);
    return 0;
}
