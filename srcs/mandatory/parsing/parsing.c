#include "pipex.h"

int main(int argc, char *argv[], char **env)
{
    t_data  *data;
    char    **paths;
    int i = 0;
    int     nb = 2;

    __pid_t child;


    if (argc < 3)
        return (printf("Error\n"), 0);
    //have to verify if the infile and outfile existes 
    data = calloc(sizeof(t_data), 1);//have to free here data
    data->env = env;
    while (env[i])//found PATH and stored all the paths in a char ** tab
    {
        if (ft_strnstr(data->env[i], "PATH", ft_strlen (data->env[i]))){
            data->paths = ft_split(data->env[i] + 5, ':');
            break ;
        }
        i++;
        //have to read each cmd and compare to it path 
    }//store the cmds
    data->cmds = calloc(sizeof(char **), argc - 3);
    while (nb < argc - 1)
    {
        data->cmds[nb] = ft_strdup(argv[nb]);//need to be freed
        printf("%s\n", data->cmds[nb]);
        nb++;
    }


    // printf("%ld\n", ft_strlenn(data->paths));




}