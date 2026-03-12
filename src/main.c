#include "../include/scanner.h"
#include "../include/ui.h"
#include "../include/player.h"
#include "../include/visualizer.h"
#include "../include/progress.h"

#include <ncursesw/ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define TITLE_WIDTH 39
#define VISUALIZER_WIDTH 40

int main()
{
    setlocale(LC_ALL, "");

    Playlist playlist = scan_music_folder("music");

    int selected = 0;
    int running = 1;
    pid_t player_pid = -1;

    time_t song_start = 0;
    int song_duration = 0;
    char current_song[256] = "";

    srand(time(NULL));

    initscr();
    noecho();
    cbreak();
    curs_set(0);

    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_CYAN);

    while (running)
    {
        /* reap finished player (avoid zombies) */
        if(player_pid > 0)
            waitpid(player_pid, NULL, WNOHANG);

        erase();

        int rows, cols;
        getmaxyx(stdscr, rows, cols);

        /* playlist width */

        int playlist_width = 0;

        for(int i = 0; i < playlist.count; i++)
        {
            int len = strlen(playlist.songs[i].name) + 2;

            if(len > playlist_width)
                playlist_width = len;
        }

        /* positions */

        int title_col = (cols - TITLE_WIDTH) / 2;
        int playlist_col = (cols - playlist_width) / 2;
        int visual_col = (cols - VISUALIZER_WIDTH) / 2;

        int start_row = rows / 2 - playlist.count / 2;
        int title_row = start_row - 8;
        int visual_row = start_row + playlist.count + 5;

        /* draw */

        draw_boxes();
        draw_title(title_row, title_col);
        draw_playlist(start_row, playlist_col, selected, &playlist);
        draw_visualizer(visual_row, visual_col);
        if (song_start > 0)
        {
            int elapsed = time(NULL) - song_start;

            int progress_row = visual_row + 6;
            int progress_col = (cols - 40) / 2;

            draw_progress_bar(
                progress_row,
                progress_col,
                current_song,
                elapsed,
                song_duration);
        }

        refresh();

        /* input */

        int ch = getch();

        if(ch != ERR)
        {
            if(ch == KEY_UP)
            {
                if(selected > 0)
                    selected--;
            }

            else if(ch == KEY_DOWN)
            {
                if(selected < playlist.count - 1)
                    selected++;
            }

            else if(ch == '\n')
            {
                char path[512];

                snprintf(
                    path,
                    sizeof(path),
                    "music/%s",
                    playlist.songs[selected].name
                );

                /* stop current song */

                if(player_pid > 0)
                {
                    kill(player_pid, SIGKILL);
                    waitpid(player_pid, NULL, 0);
                }

                /* start new player */

                strcpy(current_song, playlist.songs[selected].name);

                song_start = time(NULL);
                song_duration = get_song_duration(path);

                player_pid = fork();

                if(player_pid == 0)
                {
                    /* detach mpg123 from ncurses terminal */

                    freopen("/dev/null", "w", stdout);
                    freopen("/dev/null", "w", stderr);

                    execlp("mpg123","mpg123","-q",path,NULL);
                    _exit(1);
                }
            }

            else if(ch == 'q')
            {
                running = 0;
            }
        }

        napms(60);
    }

    /* cleanup */

    if(player_pid > 0)
    {
        kill(player_pid, SIGKILL);
        waitpid(player_pid, NULL, 0);
    }

    endwin();

    free(playlist.songs);

    return 0;
}