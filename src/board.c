#include <stdio.h>
#include <stdlib.h>
#include "board.h"

void readBoard(chess** board, char* fileName, int row, int col)
{
    FILE *fb;
    fb = fopen(fileName, "r");
    if(!fb)
    {
        printf("無法讀取檔案，結束程式\n");
        exit(0);
    }
    int i = 0, j = 0;
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            
        }
    }
}
