#ifndef UI_H
#define UI_H

#include "scanner.h"

void draw_boxes();
void draw_title(int row, int col);
void draw_playlist(int row, int col, int selected, struct Playlist *playlist);

#endif