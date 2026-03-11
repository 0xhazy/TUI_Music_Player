#include "../include/player.h"

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>

pid_t play_song(const char *path,pid_t current_pid)
{
    if(current_pid>0){
        kill(current_pid,SIGKILL);
        waitpid(current_pid,NULL,0);
    }

    pid_t pid = fork();

    if(pid==0){
        execlp("mpg123","mpg123","-q",path,NULL);
        _exit(1);
    }

    return pid;
}

void stop_player(pid_t pid)
{
    if(pid > 0)
    {
        kill(pid, SIGKILL);
        waitpid(pid, NULL, 0);
    }
}