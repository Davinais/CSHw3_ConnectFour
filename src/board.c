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
            if(readCh == 'R')
                game->rNum++;
            else if(readCh == 'Y')
                game->yNum++;
        }
    }
    fclose(fb);
    game->chessNum = game->rNum + game->yNum;
    if(!checkValid(game))
    {
        printBoard(game);
        puts("不合理的殘局，離開程式");
        exit(0);
    }
}

bool checkValid(Game* game)
{
    //剪查棋子數
    if(game->rNum - game->yNum > 1 || game->yNum > game->rNum)
    {
        return false;
    }
    game->nowPlay = (game->rNum == game->yNum)?R:Y;
    int i = 0, j = 0;
    //檢查有沒有中間被空白斷開
    for(j = 0; j < COL; j++)
    {
        bool beenPlaced = false;
        for(i = 0; i < ROW; i++)
        {
            if(game->board[i][j] == N)
            {
                if(beenPlaced)
                {
                    return false;
                }
            }
            else
            {
                if(!beenPlaced)
                    beenPlaced = true;
            }
        }
    }
    int btmhasRed = 0, nothing = 0;
    //檢查第一排是否有紅色，排除棋盤為空的情形
    for(int j = 0; j < COL; j++)
    {
        if(game->board[ROW-1][j] == R)
        {
            btmhasRed++;
        }
        else if(game->board[ROW-1][j] == N)
        {
            nothing++;
        }
    }
    if(nothing != COL && btmhasRed == 0)
    {
        return false;
    }
    chess lastPlay = (game->nowPlay == R)?Y:R;
    chess temp;
    int lastOnTop = 0;
    //檢查最頂端有沒有上一個人下的棋
    for(j = 0; j < COL; j++)
    {
        for(i = 0; i < ROW; i++)
        {
            temp = game->board[i][j];
            if(temp != N)
            {
                if(temp == lastPlay)
                    lastOnTop++;
                break;
            }
        }
    }
    if(nothing != COL && lastOnTop == 0)
    {
        return false;
    }
    return !checkWin(game); //因為最後一個就是檢查有沒有勝利，直接寫在return上了
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
    game->rNum = 0;
    game->yNum = 0;
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
    puts("１２３４５６７");
}

bool isFullCol(Game* game, int col)
{
    return (game->board[0][col] != N);
}

void placeChess(Game* game, int col)
{
    int i = 0;
    col -= 1;
    for(i = ROW-1; i >= 0; i--)
    {
        if(game->board[i][col] == N)
        {
            game->board[i][col] = game->nowPlay;
            break;
        }
    }
    game->nowPlay = (game->nowPlay == R)?Y:R;
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
    //檢查橫排
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
        rcn = 0, ycn = 0;
    }
    //檢查直列
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
        rcn = 0, ycn = 0;
    }
    rcn = 0, ycn = 0;
    int k = 0, l = 0;
    //檢查左上至右下的斜線
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
        rcn = 0, ycn = 0;
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
        rcn = 0, ycn = 0;
        i = 0;
    }
    //檢查右上至左下的斜線
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
        rcn = 0, ycn = 0;
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
        rcn = 0, ycn = 0;
        j = COL-1;
    }
    //檢查是否全滿
    int fullColNum = 0;
    for(j = 0; j < COL; j++)
    {
        if(isFullCol(game, j))
        {
            fullColNum++;
        }
    }
    if(fullColNum >= 7)
    {
        game->winner = Y;
        return true;
    }
    return false;
}
