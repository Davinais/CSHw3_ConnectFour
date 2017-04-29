#include "termctrl.h"

void gotorc(int row, int col)
{
    printf("\e[%d;%dH", row, col);
}

char* colorstr(char* target, char *str, Color color)
{
    int colornum = 8;
    int lightcode = color/colornum;
    int colorcode = color%colornum;
    sprintf(target, "\e[%d;3%dm%s\e[m", lightcode, colorcode, str);
    return target;
}

int flush_in(void)
{
    char c;
    int total = 0;
    while((c = getchar()) != '\n' && c != EOF)
    {
        total++;
    }
    return total;
}
