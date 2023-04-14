/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 23:07:43 by fgonzale          #+#    #+#             */
/*   Updated: 2023/04/14 11:44:27 by fgonzale         ###   ########.fr       */
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
	free(data->pid);
	free(data->p_fd);
	if (data->is_heredoc)
		unlink(".here_doc.tmp");
}

void	close_fds(t_data *data)
{
	if (data->infile >= 0)
		close(data->infile);
	if (data->outfile >= 0)
		close(data->outfile);
	close_pipes(data);
}

void	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->nb_cmds - 1) * 2)
	{
		close(data->p_fd[i]);
		i++;
	}
}
