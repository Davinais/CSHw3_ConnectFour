#include <stdio.h>
#include <string.h>
#include "board.h"
#include "termctrl.h"

int chartoint(char c)
{
    return c - '0';
}

int ask(char* question, char* valid, Game* game)
{
    bool err = false;
    char ch = '\0';
    do
    {
        printf("%s", question);
        ch = getchar();
        if(ch == EOF || ch == '\n') //若為EOF或換行字元，不進flush以免再度停頓在getchar()
            err = true;
        else if(flush_in() > 0) //flush函式回傳值為不包括\n或EOF字元的被清除字元數，若大於0即代表為不合法輸入
            err = true;
        else if(!strchr(valid, ch)) //檢查是否在合法選項字元之內
            err = true;
        else if(isFullCol(game, chartoint(ch)-1))
            err = true;
        else
            err = false;
        if(err)
        {
            char errbuf[80];
            printf("%s", colorstr(errbuf, "錯誤的輸入，請重新輸入！\n", RED));
        }
    }while(err);
    return chartoint(ch);
}

int main(int argc, char** argv)
{
    puts("歡迎來到四子棋的世界\n");
    Game game;
    initBoard(&game);
    if(argc == 2)
    {
        readBoard(&game, argv[1]);
    }
    char buffer[160];
    do
    {
        printBoard(&game);
        sprintf(buffer, "[玩家%d] 請輸入想要將棋下在哪列棋盤[1-7]：", game.nowPlay);
        int opt = ask(buffer, "1234567", &game);
        placeChess(&game, opt);
    }while(!checkWin(&game));
    printBoard(&game);
    printf("恭喜[玩家%d]贏得勝利！\n", game.winner);
    return 0;
}
