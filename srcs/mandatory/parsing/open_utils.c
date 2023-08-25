/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:38:11 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/08/21 13:59:16 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	utils(int nb, t_data *data)
{
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

void	open_failed(t_data *data, int first)
{
	close(data->fd[0]);
	close(data->fd[1]);
	if (!first)
		close(data->prev);
	exit(1);
}
