#include "main.h"

int main()
{
    int xVal;
    int yVal;
    int colour;

    initscr();
    noecho();
    cbreak();
    start_color();

    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    prepBoard();

    xVal = getAsciiIn();
    attron(COLOR_PAIR(3));
    mvprintw(0,0, "%d", xVal);
    attroff(COLOR_PAIR(3));
    yVal = getYValue(xVal);

    do
    {
        colour = findColour(yVal, xVal);
        changeColour(yVal, xVal, colour);

        xVal = getAsciiIn();
        yVal = getYValue(xVal);
        
        /*attron(COLOR_PAIR(3));
        mvprintw(0, 0, "Hello");
        attroff(COLOR_PAIR(3));*/
    }while (xVal != 27);
    endwin();

    return(0);
}
