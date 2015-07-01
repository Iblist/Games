#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

void prepBoard();
int findColour(int y, int x);
void changeColour(int y, int x, int colour);

#endif //DRAW_H
