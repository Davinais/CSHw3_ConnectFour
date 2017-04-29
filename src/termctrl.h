#ifndef _TERMCTRL_H_
#define _TERMCTRL_H_

#include <stdio.h>

typedef enum Color
{
    BLACK, DARK_RED, DARK_GREEN, DARK_YELLOW, DARK_BLUE, DARK_MAGENTA, DARK_CYAN, GRAY,
    DARK_GRAY, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE
}Color;

void gotorc(int, int);
char* colorstr(char*, char*, Color);
int flush_in(void);
#endif
