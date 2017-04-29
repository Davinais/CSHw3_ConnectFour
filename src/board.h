#ifndef _BOARD_H_
#define _BOARD_H_

#define ROW 6
#define COL 7

#include <stdbool.h>

typedef enum chess
{
    N, R, Y
}chess;

typedef struct Game
{
    chess board[ROW][COL];
    chess nowPlay;
    chess winner;
    int chessNum, rNum, yNum;
}Game;

void readBoard(Game*, char*);
bool checkValid(Game*);
void initBoard(Game* game);
void printBoard(Game*);
bool checkWin(Game*);
#endif
