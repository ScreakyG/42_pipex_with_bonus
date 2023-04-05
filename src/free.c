/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 23:07:43 by fgonzale          #+#    #+#             */
/*   Updated: 2023/03/19 07:07:50 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_cmd_paths(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (data->cmd_paths[i])
	{
		free(data->cmd_paths[i]);
		i++;
	}
	free(data->cmd_paths);
}

void	free_cmd_args(t_data *data)
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

void	free_parent(t_data *data)
{
	close_fds(data);
	free_cmd_paths(data);
	free(data->pipe_fd);
	if (data->is_heredoc)
		unlink(".here_doc.tmp");
}
