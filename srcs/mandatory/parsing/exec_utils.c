/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:44:59 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/08/21 14:01:46 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_paths_and_store(char **env)
{
	int		i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

void	errors_manager(t_data *data, char *curr_cmd)
{
	if (ft_strchr(curr_cmd, '/'))
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
}

void	ft_freetab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
