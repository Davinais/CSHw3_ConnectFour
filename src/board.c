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

void initBoard(Game* game)
{
    int i = 0, j = 0;
    for(i = 0; i < ROW; i++)
    {
        for(j = 0; j < COL; j++)
        {
            game->board[i][j] = N;
        }
    }
    game->chessNum = 0;
    game->nowPlay = R;
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

void checkSpace(chess ch, int* rcn, int* ycn)
{
    switch(ch)
    {
        case R:
            *ycn = 0;
            (*rcn)++;
            break;
        case Y:
            *rcn = 0;
            (*ycn)++;
            break;
        case N:
            *rcn = 0;
            *ycn = 0;
    }
}

//此函數不論雙贏情形，因為該為不合理殘局情況
bool checkWin(Game* game)
{
    int i = 0, j = 0;
    int rcn = 0, ycn = 0;
    for(i = 0; i < ROW; i++)
    {
        for(j = 0; j < COL; j++)
        {
            checkSpace(game->board[i][j], &rcn, &ycn);
            if(rcn >= 4 || ycn >= 4)
            {
                game->winner = (rcn >= 4)?R:Y;
                return true;
            }
        }
    }
    rcn = 0, ycn = 0;
    for(j = 0; j < COL; j++)
    {
        for(i = 0; i < ROW; i++)
        {
            checkSpace(game->board[i][j], &rcn, &ycn);
            if(rcn >= 4 || ycn >= 4)
            {
                game->winner = (rcn >= 4)?R:Y;
                return true;
            }
        }
    }
    rcn = 0, ycn = 0;
    int k = 0, l = 0;
    for(i = 0, j = 0; i < ROW; i++)
    {
        k = i;
        while(k < ROW && j < COL)
        {
            checkSpace(game->board[k][j], &rcn, &ycn);
            if(rcn >= 4 || ycn >= 4)
            {
                game->winner = (rcn >= 4)?R:Y;
                return true;
            }
            k++;
            j++;
        }
        j = 0;
    }
    rcn = 0, ycn = 0;
    for(i = 0, j = 0; j < COL; j++)
    {
        l = j;
        while(i < ROW && l < COL)
        {
            checkSpace(game->board[i][l], &rcn, &ycn);
            if(rcn >= 4 || ycn >= 4)
            {
                game->winner = (rcn >= 4)?R:Y;
                return true;
            }
            i++;
            l++;
        }
        i = 0;
    }
    rcn = 0, ycn = 0;
    for(i = 0, j = COL-1; j >= 0; j--)
    {
        l = j;
        while(i < ROW && l >= 0)
        {
            checkSpace(game->board[i][l], &rcn, &ycn);
            if(rcn >= 4 || ycn >= 4)
            {
                game->winner = (rcn >= 4)?R:Y;
                return true;
            }
            i++;
            l--;
        }
        i = 0;
    }
    rcn = 0, ycn = 0;
    for(i = 0, j = COL-1; i < ROW; i++)
    {
        k = i;
        while(k < ROW && j >= 0)
        {
            checkSpace(game->board[k][j], &rcn, &ycn);
            if(rcn >= 4 || ycn >= 4)
            {
                game->winner = (rcn >= 4)?R:Y;
                return true;
            }
            k++;
            j--;
        }
        j = COL-1;
    }
    return false;
}
