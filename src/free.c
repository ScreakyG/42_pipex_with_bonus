/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 23:07:43 by fgonzale          #+#    #+#             */
/*   Updated: 2023/03/12 23:22:46 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_only_pipe(t_data *data)
{
	free(data->pipe_fd);
	close(data->infile);
	close(data->outfile);
}

void	free_parent_data(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (data->cmd_paths[i])
	{
		free(data->cmd_paths[i]);
		i++;
	}
	free(data->cmd_paths);
	free(data->pipe_fd);
	close(data->infile);
	close(data->outfile);
}

void	free_child_data(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (data->cmd_args[i])
	{
		free(data->cmd_args[i]);
		i++;
	}
	free(data->cmd_args);
	free(data->cmd);
}
