#define _DEFAULT_SOURCE
#include "dirent.h"
#include "stdio.h"
#include "string.h"
#include <linux/limits.h>
#include <stdlib.h>

#include "../include/scanner.h"

int has_mp3_extension(const char *name) {
  const char *ext = strrchr(name, '.');

  if (!ext) {
    return 0;
  }
  return strcmp(ext, ".mp3") == 0;
}

Playlist scan_music_folder(const char *path) {
  DIR *dir;
  struct dirent *entry;

  Playlist playlist;
  playlist.songs = NULL;
  playlist.count = 0;

  dir = opendir(path);

  if (dir == NULL) {
    perror("opendir");
    return playlist;
  }

  while ((entry = readdir(dir)) != NULL) {

    if (entry->d_type != DT_REG)
      continue;

    if (has_mp3_extension(entry->d_name)) {
      Song *temp = realloc(playlist.songs,
                           sizeof(*playlist.songs) * (playlist.count + 1));
      if (!temp) {
        perror("realloc");
        break;
      }
      playlist.songs = temp;
      strcpy(playlist.songs[playlist.count].name, entry->d_name);

      playlist.count++;
    }
  }

  closedir(dir);

  return playlist;
}
