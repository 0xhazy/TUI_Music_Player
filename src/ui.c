#include <ncursesw/ncurses.h>
#include <string.h>
#include "../include/scanner.h"

static char *title[] = {
"██████╗ ██╗      █████╗ ██╗   ██╗ █████╗ ",
"██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝██╔══██╗",
"██████╔╝██║     ███████║ ╚████╔╝ ███████║",
"██╔═══╝ ██║     ██╔══██║  ╚██╔╝  ██╔══██║",
"██║     ███████╗██║  ██║   ██║   ██║  ██║",
"╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝"
};

void draw_title(int row, int col)
{
    for(int i=0;i<6;i++)
        mvprintw(row+i,col,"%s",title[i]);
}

void draw_boxes()
{
    int rows,cols;
    getmaxyx(stdscr,rows,cols);

    box(stdscr,0,0);

    for(int i=2;i<cols-2;i++){
        mvaddch(2,i,'-');
        mvaddch(rows-3,i,'-');
    }

    for(int i=2;i<rows-2;i++){
        mvaddch(i,2,'|');
        mvaddch(i,cols-3,'|');
    }

    for(int i=4;i<cols-4;i++){
        mvaddch(4,i,'-');
        mvaddch(rows-5,i,'-');
    }

    for(int i=4;i<rows-4;i++){
        mvaddch(i,4,'|');
        mvaddch(i,cols-5,'|');
    }
}

void draw_playlist(int row,int col,int selected,Playlist *playlist)
{
    for(int i=0;i<playlist->count;i++)
    {
        if(i==selected){
            attron(COLOR_PAIR(1));
            mvprintw(row+i,col,"> %s",playlist->songs[i].name);
            attroff(COLOR_PAIR(1));
        }
        else{
            mvprintw(row+i,col,"  %s",playlist->songs[i].name);
        }
    }
}