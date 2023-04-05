/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 01:33:36 by fgonzale          #+#    #+#             */
/*   Updated: 2023/03/19 07:12:45 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exit_error(int error_status, t_data *data)
{
	if (data)
	{
		close_fds(data);
		if (data->pipe_fd)
			free(data->pipe_fd);
		if (data->cmd_paths)
			free_cmd_paths(data);
		if (data->cmd_args)
			free_cmd_args(data);
	}
	if (data->is_heredoc)
		unlink(".here_doc.tmp");
	exit(error_status);
}

void	close_fds(t_data *data)
{
	close(data->infile);
	close(data->outfile);
	close_pipes(data);
}

int	msg(char *str, char *str2, int error)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str2, 2);
	write(2, "\n", 1);
	return (error);
}

void	cmd_err_msg(char *str, char *cmd)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
}

void	msg_error(char *str)
{
	perror(str);
	exit(1);
}
