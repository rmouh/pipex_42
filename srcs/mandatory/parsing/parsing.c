#include "pipex.h"

void    open_failed(t_data *data, int first)
{
    close(data->fd[0]);
    close(data->fd[1]);
    if (!first)
        close(data->prev);       //if is not the foirst hqve to close the prev
        //free the data
    exit(1);
}
int my_open(int nb, t_data *data)
{
    int opn;
    if (nb = 0)
    {// the first cmd
        opn = open(data->in_file, O_RDONLY, 0666);
        if (opn < 0)
            open_failed(data, 1);
    }
    else if(nb == data->cmd_size - 1)
    {
        opn = open(data->out_file, O_RDWR | O_CREAT | O_TRUNC, 0666);
        if (opn < 0)
             open_failed(data, 0);
    }
    if (errno == 13)
        return (0, ft_printf("bash: %s: Permission denied\n", data->in_file));
    else if (opn < 0)
        ft_printf("bash: %s: No such file or directory\n", data->in_file);
    else 
        open_worked(nb, data, opn);
    close (data->fd[1]);
    close (data->fd[0]);
    close(opn);
    // my_exec(data, curr_cmd, int nb)
}

void open_worked(int nb, t_data *data, int opn)
{
    if (nb == 1)
    {
        dup2(opn, STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
    }
    else  if (nb == data->cmd_size -1)
    {
        dup2(data->prev, STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
    }
    else
    {
        dup2(data->prev, STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
    }
}

void    my_exec(t_data *data, char *curr_cmd, int nb)
{
    int i;
    int exec;
 
    if (ft_strcontain(curr_cmd, "\\"))//have to directly execute
            exec = execve(curr_cmd, data->cmds, NULL);
            // break ; // execve has worked
    else {
        i = 0;
        while (i < data->path_size)
        {
            curr_cmd = ft_strjoin(data->paths[i],  data->cmds[nb]);
            exec = execve(curr_cmd, data->cmds, NULL);//need to verif if exec workked
            i++;
            free(curr_cmd);
        }// perror pour une erreur;
    }
    if(exec < 0)
    {
        if (errno == 13)
			ft_printf("bash: %s: Permission denied\n", data->cmds[nb]);
		else
			ft_printf("bash: %s: No such file or directory\n", data->cmds[nb]);
	
    }
            
}

void    find_paths_and_store(t_data   *data, char **env, int argc)
{
    int i;

    i = 0;    
    data = calloc(sizeof(t_data), 1);//have to free here data
    data->env = env;
    data->cmd_size = argc - 3;
    while (env[i])//found PATH and stored all the paths in a char ** tab
    {
        if (ft_strnstr(data->env[i], "PATH", ft_strlen (data->env[i])))
        {
            data->paths = ft_split(data->env[i] + 5, ':');
            break ;
        }
        i++;
        // have to read each cmd and compare to it path 
    }
}

void    store_cmds(t_data *data, int argc, char *argv[])
{
    int nb;

    nb = 0;
    data->path_size = ft_strlenn (data->paths);
    data->cmds = calloc(sizeof(char **), data->cmd_size);//have to free
    data->in_file = (char *)argv[0];
    data->out_file = (char *)argv[argc - 1];
    while (nb < argc - 1)
    {
        data->cmds[nb - 2] = ft_strdup(argv[nb]);//need to be freed
        // printf("%s\n", data->cmds[nb - 2]);
        nb++;
    }
}

int main(int argc, char *argv[], char **env)
{
    t_data  *data;
    char    **paths;
    int i = 0;
    int     nb = 2;
    char    *curr_cmd;
    int     ok;
    int opn;

    __pid_t child;

    nb = 0;
    if (argc < 3)
        return (printf("Error\n"), 0);
    //have to verify if the infile and outfile existes 
    find_paths_and_store(data, env, argc);
    ///store the cmds
    store_cmds(data, argc, argv);
    //test the args with the paths 
    data->pids = calloc(sizeof(__pid_t), data->cmd_size);
    while (nb < data->cmd_size)
    {//liree de 0 ecrire 1
        pipe(data->fd);//ouvre de fd sur le ;e;e ficher un en lecture + ecriture
        child = fork();//dup2(fd de infile, stdin_filno)//stdin point sur le infile /// vers prive
        data->pids[nb] = child;// dup2(fd out de lq command)sortie stqndqr derige vers fd[1] // vers 1
        curr_cmd = data->cmds[nb];
        if (child = 0)
        {
            my_open(nb, data);
            my_exec(data, curr_cmd, nb);
        }
        else
        {
            if (data->prev != -1)
                close(data->prev);
            data->prev = data->fd[0];
            close(data->fd[1]);
        }
        nb++;
    }
    close(data->fd[0]);
        // wait_pid
}


    // printf("%ld\n", ft_strlenn(data->paths));


