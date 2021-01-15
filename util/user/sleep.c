#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {

    if (argc == 1) {
        char msg[] = "no arguments!\n";
        write(1, msg, strlen(msg));
        exit(1);
    }

    if (argc > 2) {
        char msg[] = "too many arguments!\n";
        write(1, msg, strlen(msg));
        exit(1);
    }

    int time_length = atoi(argv[1]);
    sleep(time_length);
    exit(0);
}