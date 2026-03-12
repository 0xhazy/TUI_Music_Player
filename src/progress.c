#include "../include/progress.h"

#include <ncursesw/ncurses.h>
#include <stdio.h>
#include <string.h>

#define BAR_WIDTH 24

int get_song_duration(const char *path)
{
    char cmd[512];
    snprintf(
        cmd,
        sizeof(cmd),
        "ffprobe -v error -show_entries format=duration -of default=noprint_wrappers=1:nokey=1 \"%s\"",
        path
    );

    FILE *fp = popen(cmd, "r");
    if(!fp)
        return 0;

    float duration = 0;
    fscanf(fp, "%f", &duration);

    pclose(fp);

    return (int)duration;
}

void draw_progress_bar(int row, int col, const char *song, int elapsed, int total)
{
    if(total <= 0)
        return;

    float ratio = (float)elapsed / total;

    int filled = ratio * BAR_WIDTH;

    char bar[BAR_WIDTH + 1];

    for(int i=0;i<BAR_WIDTH;i++)
    {
        if(i < filled)
            bar[i] = '#';
        else
            bar[i] = '-';
    }

    bar[BAR_WIDTH] = '\0';

    int em = elapsed / 60;
    int es = elapsed % 60;

    int tm = total / 60;
    int ts = total % 60;

    mvprintw(row, col, "Now Playing: %s", song);

    mvprintw(
        row + 1,
        col,
        "[%s] %02d:%02d / %02d:%02d",
        bar,
        em, es,
        tm, ts
    );
}