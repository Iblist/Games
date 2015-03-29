#ifndef PACMAN_INCLUDE_PACMAN_H_
#define PACMAN_INCLUDE_PACMAN_H_
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#endif  // PACMAN_INCLUDE_PACMAN_H_

/*typedef for a rectangle.  Used to draw rectangles.
  Contains height and width.  Type is rectangle*/
typedef struct rectangle
{
    int height;
    int width;
}rectangle;

/*Takes a rectangle pointer.  Rectangle contains
  two integers*/
void drawBoard(rectangle * rectptr);

/*Draws a rectangle at indicated space,
  Expects rectangle pointer and two integers as
  Arguments*/
void drawRect(rectangle * rectptr, int ypos, int xpos);

/*Adds pellets to pacman board.  Expects no arguments*/
void addPellets();

/*Moves players cursor, expects a character*/
void moveCursor(char direction);

/*Checks if users input is valid.  Expects no arguments*/
void falseInput();

/*Moves pacman, expects two integers as coordinates*/
void movePacMan(int ypos, int xpos);

/*Checks if a space is valid to be moved to
  Expects two integers as coordinates
  Returns a 1 if moveable.
  Returns a 0 if not moveable*/
int moveable(int ypos, int xpos);
