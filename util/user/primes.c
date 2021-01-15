#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void a(int *num, int len, int times)
{
    if (len == 0)
    {
        exit(0);
    }
    int pid;
    int fds[2];
    pipe(fds);
    pid = fork();
    int i;

    if (pid == 0)
    {
        close(fds[1]);
        int buf[100];
        i = 0;
        int n;
        while (1)
        {
            n = read(fds[0], buf + i, 4);
            i++;
            if (n == 0) {
                break;
            }
        }
        printf("pid : %d  len2: %d\n", getpid(), i-1);
        printf("prime %d\n", buf[0]);
        printf("#######\n");
        close(fds[0]);
        printf("!!!!!\n");
        a(buf, i - 1, times + 1);
        exit(0);
    }
    else
    {
        close(fds[0]);
        printf("pid : %d   times : %d    len : %d\n", getpid(), times, len);
        for (i = 1; i < len; i++)
        {
            if (*(num + i) % times != 0)
            {
                printf("%d\n", *(num + i));
                write(fds[1], num + i, 4);
            }
        }
        close(fds[1]);
        //wait((int *)0);
    }
}

int main(int argc, char const *argv[])
{
    // int prime_num[35];

    // //int pid;
    // //int buf;

    // for (i = 0; i < 35; i++)
    // {
    //     prime_num[i] = i + 2;
    // }

    //a(prime_num, 35, 2);
    int i;
    int len = 35;
    int times = 2;
    int buf[35];
    for (i = 0; i < 35; i++)
    {
        buf[i] = i + 2;
    }
    while(1) {
        if (len == 0)
        {
            exit(0);
        }
        int pid;
        int fds[2];
        pipe(fds);
        pid = fork();
        int i;

        if (pid == 0)
        {
            close(fds[1]);
            i = 0;
            int n;
            while (1)
            {
                n = read(fds[0], buf + i, 4);
                i++;
                if (n == 0)
                {
                    break;
                }
            }
            //printf("prime %d\n", buf[0]);
            close(fds[0]);
            times++;
            len = i - 1;
        }
        else
        {
            close(fds[0]);
            printf("prime %d\n", buf[0]);
            for (i = 1; i < len; i++)
            {
                if (*(buf+ i) % times != 0)
                {
                    //printf("%d\n", *(buf + i));
                    write(fds[1], buf + i, 4);
                }
            }
            len = i -1;
            close(fds[1]);
            wait((int *)0);
            exit(0);
        }
    }

    wait((int *)0);

    // for (i = 0; i < 11; i++)
    // {
    //     pid = fork();

    //     if (pid == 0)
    //     {
    //         read(fds[0], &buf, 4);
    //         printf("prime %d\n", buf);
    //         close(fds[0]);
    //         close(fds[1]);
    //         exit(0);
    //     }
    //     else
    //     {
    //         write(fds[1], prime_num + i, 4);
    //         wait((int *)0);
    //         if (i == 10)
    //         {
    //             close(fds[0]);
    //             close(fds[1]);
    //         }
    //     }
    // }

    exit(0);
}
