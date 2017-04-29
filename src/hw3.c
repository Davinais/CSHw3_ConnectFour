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
        for(i = 0; i < ROW; i++)
        {
            for(j = 0; j < COL; j++)
            {
                game.board[i][j] = N;
            }
        }
        game.chessNum = 0;
        game.nowPlay = R;
    }
    printBoard(&game);
    return 0;
}
