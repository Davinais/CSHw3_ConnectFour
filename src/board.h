#ifndef _BOARD_H_
#define _BOARD_H_

#define ROW 6
#define COL 7

typedef enum chess
{
    N, R, Y
}chess;

typedef struct Game
{
    chess board[ROW][COL];
    chess nowPlay;
    int chessNum;
}Game;

void readBoard(Game*, char*);
void initBoard(Game* game);
void printBoard(Game*);
#endif
