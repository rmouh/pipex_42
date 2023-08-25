/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:36:01 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/08/21 14:04:28 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
	// ./pipex infile cat ls lsblk grep wc outfile

	// cat va lire dans infile
	// cat va ecrire vers ls
	// ls lire vers cat
	// ls ecrire vers lsblk
	// ...
	// wc lire vers grep
	// wc ecrire vers outfile
*/

void	my_open(int nb, t_data *data)
{
	int	opn;

	if (nb == 0)
	{
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
	utils(nb, data);
}

void	my_exec(t_data *data, char *curr_cmd)
{
	int		i;
	char	*cmd;

	i = 0;
	errors_manager(data, curr_cmd);
	while (data->paths[i])
	{
		cmd = ft_strjoine(data->paths[i], curr_cmd);
		if (access(cmd, F_OK | X_OK) != -1)
			execve(cmd, data->cmds, data->env);
		free(cmd);
		i++;
	}
	if (data->paths)
		ft_freetab(data->paths);
	if (errno == 13)
		ft_printf("bash: %s: Permission denied\n", curr_cmd);
	else
		ft_printf("bash: %s: No such file or directory\n", curr_cmd);
}

/*
	found PATH and stored all the paths in a char ** tab
*/

void	here_doc(t_data *data, char *deli)
{
	int		fd;
	char	*str;
	char	*delim;

	delim = ft_strjoinn(deli, "\n");
	fd = open("/tmp/here_doc", O_CREAT | O_RDWR, 0666);
	if (fd == -1)
		exit(1);
	while (1)
	{
		str = get_next_line(0, 0);
		if (!str)
			break ;
		ft_putstr_fd(str, fd);
		if (!ft_strncmp(delim, str, ft_strlen(delim)))
			break ;
		free(str);
	}
	free(str);
	free(delim);
	get_next_line(1, 1);
	close(fd);
	data->in_file = "/tmp/here_doc";
	data->here_doc = 1;
	data->cmd_size -= 1;
}

int	main(int argc, char *argv[], char **env)
{
	static t_data	data = {0};
	int				nb;

	nb = 0;
	if (argc < 5)
		return (ft_printf("Error\n"), 0);
	init(&data, argv, argc, env);
	if (!ft_strncmp("here_doc", argv[1], ft_strlen("here_doc")))
		here_doc(&data, argv[2]);
	data.pids = malloc(sizeof(__pid_t) * data.cmd_size);
	while (nb < data.cmd_size)
	{
		pipe(data.fd);
		data.pids[nb] = fork();
		if (data.pids[nb] == 0)
			first_case(&data, nb, argv);
		else
			second_case(&data);
		nb++;
	}
	close(data.fd[0]);
	last(&data);
}
