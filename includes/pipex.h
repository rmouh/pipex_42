# ifndef PIPEX_H
# define PIPEX_H

#include "libft.h"
#include<stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct  s_data
{
    char    **paths;
    char    **env;
    char    **cmds;
}               t_data;


#endif