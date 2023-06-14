#include "includes/pipex.h"

int main(int ac, char **av, char **env)
{
    char *str;

    int pid = fork();

    if (pid == 0)
    {
        str = malloc(100);
        free(str);
        exit(1);
    }
    if (pid > 0)
    {
    
    }
    free(str);
}