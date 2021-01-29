#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
    char *argv_2[MAXARG];

    char get_char[1];

    char argument[64];
    memset(argument, 0, sizeof(argument));

    for (int c = 1; c < argc; ++c)
    {
        argv_2[c - 1] = argv[c];
    }

    int i = 0;
    while (read(0, get_char, sizeof(get_char)) != 0)
    {
        if (get_char[0] != '\n')
        {
            argument[i++] = get_char[0];
        }
        else
        {

            argv_2[argc - 1] = argument;
            argv_2[argc] = 0;

            if (fork() == 0)
            {
                // printf("arguments: ");
                // for(int j = 0; j <= argc - index; ++j){
                //     printf("%s ", argv_2[j]);
                // }
                // printf("\n");

                // int d = 0;
                // printf("the arguments of child process: ");
                // while (argv_2[d])
                // {
                //     printf("%s ", argv_2[d++]);
                // }
                // printf("\n");

                // printf("the arguments of child process: ");
                // for (int g = 0; g < argc; ++g)
                // {
                //     printf("%s ", argv_2[g]);
                // }
                // printf("\n");

                exec(argv_2[0], argv_2);
            }
            else
            {

                wait(0);
                memset(argument, 0, sizeof(argument));
                i = 0;
            }
        }
    }

    exit(0);
}