#include <stdio.h>
#define ROW 6
#define COL 7

int main(int argc, char** argv)
{
    char board[COL][ROW];
    int i = 0, j = 0;
    for(i = 0; i < COL; i++)
    {
        for(j = 0; j < ROW; j++)
        {
            board[i][j] = NULL;
        }
    }
}

