#ifndef SCANNER_H
#define SCANNER_H

typedef struct {
  char name[256];
} Song;

typedef struct Playlist {
  Song *songs;
  int count;
} Playlist;

Playlist scan_music_folder(const char *path);

#endif
