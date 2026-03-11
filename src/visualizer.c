#include <ncursesw/ncurses.h>
#include <stdlib.h>

void draw_visualizer(int row,int col)
{
    int bars = 20;

    for(int i=0;i<bars;i++)
    {
        int height = rand()%5;

        for(int j=0;j<height;j++)
        {
            mvprintw(row-j,col+i*2,"|");
        }
    }
}