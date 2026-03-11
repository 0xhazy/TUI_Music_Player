#ifndef PLAYER_H
#define PLAYER_H

#include <sys/types.h>

pid_t play_song(const char *path, pid_t current_pid);

void stop_player(pid_t pid);

#endif