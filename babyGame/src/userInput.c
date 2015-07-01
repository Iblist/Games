#include "userInput.h"

int getAsciiIn()
{
    char userInput;
    int asciiValue;

    userInput = getch();
    asciiValue = userInput;
    return asciiValue;
}

int getYValue(int x)
{
    int y;

    y = sin(x) * 10 + 20;

    return y;
}
