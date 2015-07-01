#include "draw.h"

void prepBoard()
{
    int y, x;
    int i, j;

    /*init_pair(1, COLOR_BLACK, COLOR_BLACK);*/

    attron(COLOR_PAIR(1));

    getmaxyx(stdscr, y, x);

    for(i=0; i < y; i++)
    {
        for(j=0; j < x; j++)
        {
            mvaddch(i, j, 'B');
        }
    }
    move(0,0);
    refresh();
    attroff(COLOR_PAIR(1));
}

int findColour(int y, int x)
{
    char localChar;
    int colour; //Black will be 0, White will be 1

    move(y, x);
    localChar = inch();

    if (localChar == 'B')
    {
        colour = 0;
    }
    else if (localChar == 'W')
    {
        colour = 1;
    }
    else
    {
        exit(0);
    }
    return colour;
}

void changeColour(int y, int x, int colour)
{
    if (colour == 1)
    {
        attron(COLOR_PAIR(1));
        mvprintw(y, x, "B");
        attroff(COLOR_PAIR(1));
    }
    else if (colour == 0)
    {
        attron(COLOR_PAIR(2));
        mvprintw(y, x, "W");
        attroff(COLOR_PAIR(2));
    }
    refresh();
}
