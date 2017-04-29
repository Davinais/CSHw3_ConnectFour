#include <stdio.h>
#include "board.h"

int main(int argc, char** argv)
{
    Game game;
    int i = 0, j = 0;
    if(argc == 2)
    {
        readBoard(&game, argv[1]);
    }
    else
    {
        initBoard(&game);
    }
    printBoard(&game);
    return 0;
}
