#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
char *
fmtname(char *path)
{
    static char buf[DIRSIZ + 1];
    char *p;

    // Find first character after last slash.
    for (p = path + strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;

    // Return blank-padded name.
    if (strlen(p) >= DIRSIZ)
        return p;
    memmove(buf, p, strlen(p));
    buf[strlen(p)] = 0;
    return buf;
}
void Find(char *path, char *goal)
{
    char buff[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(path, 0)) < 0)
    {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch (st.type)
    {
    case T_FILE:
        //printf("path %s\n", path);
        if (strcmp(fmtname(path), goal) == 0)
        {
            printf("%s\n", path);
        }
        break;

    case T_DIR:
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof(buff))
        {
            printf("find: path too long\n");
            break;
        }
        
        strcpy(buff, path);
        p = buff + strlen(buff);
        *p++ = '/';

        while (read(fd, &de, sizeof(de)) == sizeof(de))
        {
            if (de.inum == 0)
                continue;

            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;

            if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
            {
                continue;
            }

            Find(buff, goal);
        }
        break;
    }
    close(fd);
    return;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(2, "find failed\n");
        exit(1);
    }
    Find(argv[1], argv[2]);
    exit(0);
}