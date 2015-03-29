/*************************pacman.c****************************
Student Name: Tyler Hoskins                  Student Number:0864693
Date: January 23 2015                        Course Name: CIS*2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/
#include "pacman.h"

/*The thing that makes the program go like voom*/
int main()
{
    char userInput;
    
    initscr();
    noecho();
    cbreak();

    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLUE);
    attron(COLOR_PAIR(1));
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);

    /*rectangle mazeBlock;
    rectangle * mazeBlockptr;
    mazeBlockptr = &mazeBlock;*/

    rectangle * mazeBlockptr = malloc(sizeof(rectangle));

    drawBoard(mazeBlockptr);
    free(mazeBlockptr);
    addPellets();

    attron(COLOR_PAIR(2));
    mvaddch(10, 24, '@');
    attroff(COLOR_PAIR(2));
    move(10, 24);

    userInput = getch();

    while (userInput != 'q')
    {
        moveCursor(userInput);
        userInput = getch();
        refresh();
    }
    endwin();

    return 0;
}

/*Draws a blue square for the playing space.
  Expects two integers, a pointer pointing to a struct,
  and no returns.
*/
void drawBoard(rectangle * rectptr)
{
    int i;

    attron(COLOR_PAIR(1));

    mvaddch(1, 24, '-');

    for (i=0; i < 23; i++)
    {
        mvaddch(i, 0, '-');
        mvaddch(i, 48, '-');
    }
    for (i=0; i < 49; i++)
    {
        mvaddch(0, i, '-');
        mvaddch(23, i, '-');
    }

    rectptr->height = 3;
    rectptr->width = 1;
    drawRect(rectptr, 1, 24);

    rectptr->height = 2;
    rectptr->width = 3;
    drawRect(rectptr, 2, 2);
    drawRect(rectptr, 2, 44);

    rectptr->width = 17;
    drawRect(rectptr, 2, 6);
    drawRect(rectptr, 2, 26);

    rectptr->width = 3;
    rectptr->height = 1;
    drawRect(rectptr, 5, 2);
    drawRect(rectptr, 5, 44);

    rectptr->width = 6;
    rectptr->height = 7;
    drawRect(rectptr, 5, 6);
    drawRect(rectptr, 5, 37);

    rectptr->width = 23;
    rectptr->height = 1;
    drawRect(rectptr, 5, 13);
    
    rectptr->width = 1;
    rectptr->height = 4;
    drawRect(rectptr, 6, 24);

    rectptr->width = 11;
    rectptr->height = 3;
    drawRect(rectptr, 7, 12);
    drawRect(rectptr, 7, 26);
    
    rectptr->width = 4;
    rectptr->height = 10;
    drawRect(rectptr, 7, 1);
    drawRect(rectptr, 7, 44);

    rectptr->width = 23;
    rectptr->height = 4;
    drawRect(rectptr, 11, 13);

    rectptr->width = 6;
    rectptr->height = 4;
    drawRect(rectptr, 13, 6);
    drawRect(rectptr, 13, 37);
 
    rectptr->width = 23;
    rectptr->height = 1;
    drawRect(rectptr, 16, 13);

    rectptr->width = 1;
    rectptr->height = 3;
    drawRect(rectptr, 17, 24);

    rectptr->width = 21;
    rectptr->height = 2;
    drawRect(rectptr, 18, 2);
    drawRect(rectptr, 18, 26);

    rectptr->width = 45;
    rectptr->height = 1;
    drawRect(rectptr, 21, 2);

    attroff(COLOR_PAIR(1));
   
}

/*
  Draws a rectangle at an indicated space.
  Expects a rectangle pointer (rectangle contains
  Two integers) and two integer pointers
*/
void drawRect(rectangle * rectptr, int ypos, int xpos)
{
    int height, width, y, x;

    height = rectptr->height;
    width = rectptr->width;

    for (y=ypos; y < ypos+height; y++)
    {
        for (x=xpos; x < xpos+width; x++)
        {
            mvaddch(y, x, '-');
        }
    }

}

/*Adds pellets to maze.  The walls are made of '-'
  So it simply places a '.' on every space without a 
  '.'  Does not expect any arguments.*/
void addPellets()
{
   int ypos, xpos;
   char currentChar;
   
   for (xpos =0; xpos < 49; xpos++)
   {
       for (ypos = 0; ypos < 23; ypos++)
       {
           currentChar = mvinch(ypos, xpos);
           if (currentChar != '-')
           {
               /*Previously printed an astericks, but after
                 Careful consideration, I have reconsidered
                 the decision to use an astericks.  In short,
                 The @ symbol, which I am using as my pacman,
                 Means 'Monkey' in Polish.  During an intellectual
                 Conversation I was having with some of my
                 Peers, it was decided a monkey eating a period
                 Would be far more comical than a monkey eating
                 A star.  Thus, in this and future versions I 
                 Will be using a period, for the sake of "lulz"
               */
               mvaddch(ypos, xpos, '.');
           }
       } 
   } 
}

/*Takes user input and decides what to do with it expects
  A character.*/
void moveCursor(char direction)
{
    int ypos, xpos, cypos, cxpos;    
    getyx(stdscr, ypos, xpos);
    getyx(stdscr, cypos, cxpos);

    /*Switch taking direction, the users input,
      and decides what to do based on that
      standard wasd controls.*/
    switch (direction)
    {
        case 'w':
            ypos--;
            break;
        case 's':
            ypos++;
            break;
        case 'a':
            xpos--;
            break;
        case 'd':
            xpos++;
            break;
        default:
            falseInput();
    }

    if (moveable(ypos, xpos) == 1)
    {
        mvaddch(ypos, xpos, ' ');
        move(cypos, cxpos);
        movePacMan(ypos, xpos);
    }
    else
    {
        move(cypos, cxpos);
    }

    refresh();
}

/*If user inputs an invalid key, function is called.
  Prints an error message to the bottom right corner
  Of the screen.  No expected arguments or returns*/
void falseInput()
{
    char string[] = "Invalid Key!!!!";    
    char clean[] = "                ";
    int ymax;
    int xmax;
    int ypos, xpos;

    getyx(stdscr, ypos, xpos);

    getmaxyx(stdscr, ymax, xmax);
    mvprintw(ymax-1, xmax-strlen(clean), "%s", clean);
    mvprintw(ymax-1, xmax-strlen(string), "%s", string); 
    getch();
    mvprintw(ymax-1, xmax-strlen(clean), "%s", clean);
    move(ypos, xpos);

}

/*Checks if the space the player is trying to
  Move to is a valid space.  If the space contains
  A '-', the space is invalid and a 0 is returned.
  If not, a 1 is returned.  Expects two integers
  Arguments*/
int moveable(int ypos, int xpos)
{
    int returnValue = 0;
    char currentChar;

    currentChar = mvinch(ypos, xpos);

    if (currentChar == '-')
    {
        returnValue = 0;
        /*mvprintw(0, 50, "%d, %d, invalid.", ypos, xpos);*/
    }
    else
    {
        returnValue = 1;
        /*mvprintw(0, 50, "%d, %d, valid.", ypos, xpos);*/
    }
    return returnValue;
}

/*Moves pacman to the proper space and removes
  The previous instance of pacman.  Expects two
  integers, ypos and xpos.  No returns*/
void movePacMan(int ypos, int xpos)
{
    
    addch(' ');
    move(ypos, xpos);
    attron(COLOR_PAIR(2));
    addch('@');
    move(ypos, xpos);
    attroff(COLOR_PAIR(2));

}

