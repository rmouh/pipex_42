#include "pipex.h"

void	open_failed(t_data *data, int first)
{
	close(data->fd[0]);
	close(data->fd[1]);
	if (!first)
		close(data->prev); //if is not the foirst hqve to close the prev
	//free the data
	exit(1);
}

// ./pipex infile cat ls lsblk grep wc outfile

// cat va lire dans infile
// cat va ecrire vers ls
// ls lire vers cat
// ls ecrire vers lsblk
// ...
// wc lire vers grep
// wc ecrire vers outfile

void	my_open(int nb, t_data *data)
{
	int	opn;

	if (nb == 0)
	{ // the first cmd
		opn = open(data->in_file, O_RDONLY);
		if (opn < 0)
			open_failed(data, 1);
		dup2(opn, STDIN_FILENO);
		close(opn);
	}
	else if (nb == data->cmd_size - 1)
	{
		opn = open(data->out_file, O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (opn < 0)
			open_failed(data, 0);
		dup2(opn, STDOUT_FILENO);
		close(opn);
	}
	if (nb != 0)
	{
		dup2(data->prev, STDIN_FILENO);
		close(data->prev);
	}
	if (nb != data->cmd_size - 1)
	{
		dup2(data->fd[1], STDOUT_FILENO);
	}
	close(data->fd[1]);
	close(data->fd[0]);
}

void	ft_freetab(char **tab)
{
	if (!tab)
		return ;
	for (int i = 0; tab[i]; i++)
		free(tab[i]);
	free(tab);
}

void	my_exec(t_data *data, char *curr_cmd)
{
	int	i;

	i = 0;
	if (ft_strchr(curr_cmd, '/')) //have to directly execute
	{
		if (access(curr_cmd, F_OK | X_OK) != -1)
			execve(curr_cmd, data->cmds, data->env);
		ft_freetab(data->cmds);
		ft_printf("Command not found\n");
		exit (1);
	}
	data->paths = find_paths_and_store(data->env);
	if (!data->paths)
	{
		ft_printf("bash: %s: No such file or directory\n", curr_cmd);
		ft_freetab(data->cmds);
		exit (1);
	}
	while (data->paths[i])
	{
		char *cmd = ft_strjoine(data->paths[i], curr_cmd);
		if (access(cmd, F_OK | X_OK) != -1)
			execve(cmd, data->cmds, data->env);
		free(cmd);
		i++;
	} // perror pour une erreur;
	if (data->paths)
		ft_freetab(data->paths);
	if (errno == 13)
		ft_printf("bash: %s: Permission denied\n", curr_cmd);
	else
		ft_printf("bash: %s: No such file or directory\n", curr_cmd);
}

char **find_paths_and_store(char **env)
{
	int		i;

	i = 0;
	while (env && env[i]) //found PATH and stored all the paths in a char ** tab
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

int	main(int argc, char *argv[], char **env)
{
	static t_data	data = {0};
	int				nb;

	nb = 0;
	if (argc < 5)
		return (ft_printf("Error\n"), 0);
	data.cmd_size = argc - 3;
    data.env = env;
    data.prev = -1;
	data.in_file = argv[1];
	data.out_file = argv[argc - 1];
    data.pids = malloc(sizeof(__pid_t) * data.cmd_size);
	while (nb < data.cmd_size)
	{                          //liree de 0 ecrire 1
		pipe(data.fd);         //ouvre de fd sur le ;e;e ficher un en lecture
		data.pids[nb] = fork();        //dup2(fd de infile,
		if (data.pids[nb] == 0)
		{
            free(data.pids);
			my_open(nb, &data);
			// store_cmds(&data, argc, argv);
		    data.cmds = ft_split(argv[nb + 2], ' ');
			if (!data.cmds)
				exit(1);
			my_exec(&data, data.cmds[0]);
			ft_freetab(data.cmds);
			exit (127);
		}
		else
		{
			if (data.prev != -1)
				close(data.prev);
			data.prev = data.fd[0];
			close(data.fd[1]);
		}
		nb++;
	}
	close(data.fd[0]);
    for (int i = 0; i < data.cmd_size; i++)
        waitpid(data.pids[i], 0, 0);
    free(data.pids);
	printf("done\n");
}

// ft_printf("%ld\n", ft_strlenn(&data->paths));
