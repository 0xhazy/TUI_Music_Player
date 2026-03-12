#ifndef PROGRESS_H
#define PROGRESS_H

int get_song_duration(const char *path);
void draw_progress_bar(int row, int col, const char *song, int elapsed, int total);

#endif