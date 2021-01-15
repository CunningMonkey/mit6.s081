#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char file_name_tmp[DIRSIZ + 1];

void fmtname(char *path)
{
    char *p;
    int i;

    for (i = 0; i < DIRSIZ + 1; i++)
        file_name_tmp[i] = '\0';

    // Find first character after last slash.
    for (p = path + strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;

    strcpy(file_name_tmp, p);
}

void find(char *path, char *file_name)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(path, 0)) < 0)
    {
        fprintf(2, "find: cannot open %s \n", path);
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s\n");
    }

    switch (st.type)
    {
    case T_FILE:
        fmtname(path);
        if (strcmp(file_name, file_name_tmp) == 0)
        {
            printf("%s\n", path);
        }

        break;
    case T_DIR:
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
        {
            printf("ls: path too long\n");
            break;
        }
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        *p++ = '\0';
        while (read(fd, &de, sizeof(de)) == sizeof(de))
        {   
            if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
                continue;
            if (de.inum == 0)
                continue;
            char tmp[10];
            strcpy(tmp, buf);
            char *end = tmp + strlen(tmp);
            strcpy(end, de.name);
            find(tmp, file_name);
        }
        break;
    default:
        break;
    }
    close(fd);
}

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        printf("Too few arguments!\n");
        exit(0);
    }

    if (argc > 3)
    {
        printf("Too many arguments!\n");
        exit(0);
    }

    char *path = argv[1];
    char *file_name = argv[2];

    find(path, file_name);

    exit(0);
}