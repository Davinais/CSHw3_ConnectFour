#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "termctrl.h"

chess chartoChess(char a)
{
    switch(a)
    {
        case 'R':
            return R;
        case 'Y':
            return Y;
        case 'N':
        default:
            return N;
    }
}
char* chesstoStr(char* target, chess a)
{
    switch(a)
    {
        case R:
            return colorstr(target, "⚉", RED); //⬤
        case Y:
            return colorstr(target, "⚇", YELLOW);; //◯
        case N:
        default:
            return colorstr(target, "◌", GRAY);; //⬚
    }
}

void readBoard(Game* game, char* fileName)
{
    FILE* fb;
    fb = fopen(fileName, "r");
    if(!fb)
    {
        puts("無法讀取檔案，離開程式");
        exit(0);
    }
    int i = 0, j = 0;
    char readCh = '\0';
    for(i = 0; i < ROW; i++)
    {
        for(j = 0; j < COL; j++)
        {
            fscanf(fb, "%c ", &readCh);
            game->board[i][j] = chartoChess(readCh);
        }
    }
    fclose(fb);
}

void printBoard(Game* game)
{
    int i = 0, j = 0;
    char buf[20];
    for(i = 0; i < ROW; i++)
    {
        for(j = 0; j < COL; j++)
        {
            printf("%s ", chesstoStr(buf, game->board[i][j]));
        }
        puts("");
    }
}
