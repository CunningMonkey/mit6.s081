#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int main(int argc, char *argv[])
{
    int fd = 0;
    int i, j;

    char buf[100];

    for (i = 1; i < argc; i++) {
        strcpy(buf + strlen(buf), *(argv + i));
        strcpy(buf + strlen(buf), " ");
    }

    read(fd, buf + strlen(buf), sizeof(buf) - strlen(buf));

    int argc_sum = 1;
    int flag;
    for ( i = 0; i < strlen(buf); i++)
    {
        flag = 0;
        while(buf[i] == ' ') {
            i++;
            if (flag == 0) {
                argc_sum++;
                flag = 1;
            }
        }
    }

    printf("exec:%s", buf);

    //char** argv_final = malloc(sizeof(char)*100);
    for (i = 0; i < argc; i++) {
        for (j = 0; j < strlen(argv[i]); j++) {
            printf("%c\n", argv[i][j]);
            argv[i][j] = '\0';
        }
    }

    j = 0;
    int k = 0;
    for(i = 0; i < strlen(buf); i++) {
        //printf("buf: ,%c, \n", buf[i]);
        flag = 0;
        while(buf[i] != ' ' && i < strlen(buf) && buf[i] != '\n') {
            flag = 1;
            //printf("buf: ,%c, \n", buf[i]);
            argv[j][k++] = buf[i++];
        }
        //printf("argv: %s,\n", argv[j]);
        if (flag == 1) {
            j++;
        }
        k = 0;
    }

    for ( i = 0; i < j; i++)
    {
        printf("%s\n", argv[i]);
    }

    if (fork() == 0)
    {
        exec(argv[0], argv);
        printf("hah\n");
        exit(1);
    }
    else
    {
        wait(0);
    }
    exit(0);
}



