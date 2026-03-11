#include "../include/scanner.h"
#include "../include/ui.h"
#include "../include/player.h"
#include "../include/visualizer.h"

#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <locale.h>

int main()
{
    Playlist playlist = scan_music_folder("music");

    int selected = 0;
    int running = 1;

    pid_t player_pid = -1;

    srand(time(NULL));
    setlocale(LC_ALL, "");

    /* ncurses init */
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_CYAN);

    clear();
    draw_boxes();
    refresh();

    while (running)
    {
        

        int rows, cols;
        getmaxyx(stdscr, rows, cols);

        

        /* center calculation */
        int max_len = 15;

        for (int i = 0; i < playlist.count; i++)
        {
            int len = strlen(playlist.songs[i].name) + 2;
            if (len > max_len)
                max_len = len;
        }

        int total_height = playlist.count + 3;

        int start_row = (rows - total_height) / 2;
        int start_col = (cols - max_len) / 2;

        draw_title(start_row - 6, start_col);

        draw_playlist(start_row, start_col, selected, &playlist);

        draw_visualizer(start_row + playlist.count + 5, start_col);

        refresh();

        int ch = getch();

        if (ch != ERR)
        {
            if (ch == KEY_UP)
            {
                if (selected > 0)
                    selected--;
            }
            else if (ch == KEY_DOWN)
            {
                if (selected < playlist.count - 1)
                    selected++;
            }
            else if (ch == '\n')
            {
                char path[512];

                snprintf(
                    path,
                    sizeof(path),
                    "music/%s",
                    playlist.songs[selected].name);

                player_pid = play_song(path, player_pid);
            }
            else if (ch == 'q')
            {
                running = 0;
            }
        }

        napms(120);
    }

    stop_player(player_pid);

    endwin();

    free(playlist.songs);

    return 0;
  }
