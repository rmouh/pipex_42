/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:40:47 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/08/21 13:58:52 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
	initialising the static variable 
*/

void	init(t_data *data, char *argv[], int argc, char **env)
{
	data->cmd_size = argc - 3;
	data->env = env;
	data->prev = -1;
	data->in_file = argv[1];
	data->out_file = argv[argc - 1];
}

void	first_case(t_data *data, int nb, char *argv[])
{	
	free(data->pids);
	my_open(nb, data);
	data->cmds = ft_split(argv[nb + 2 + data->here_doc], ' ');
	if (!data->cmds)
		exit(1);
	my_exec(data, data->cmds[0]);
	ft_freetab(data->cmds);
	exit (127);
}

void	second_case(t_data *data)
{
	if (data->prev != -1)
		close(data->prev);
	data->prev = data->fd[0];
	close(data->fd[1]);
}

void	last(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_size)
	{
		waitpid(data->pids[i], 0, 0);
		i++;
	}
	free(data->pids);
}
