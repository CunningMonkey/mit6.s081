#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int pid;
    int fds[2];
    char buf[100];

    pipe(fds);

    pid = fork();

    if (pid == 0) {
        read(fds[0], buf, sizeof(buf));
        pid = getpid();
        printf("%d: received %s\n", pid, buf);
        write(fds[1], "pong\n", 5);
    } else {
        write(fds[1], "ping\n", 5);
        pid = getpid();
        int status;
        wait(&status);
        read(fds[0], buf, 5);
        printf("%d: received %s\n", pid, buf);

    }
    exit(0);
}