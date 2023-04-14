/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 01:33:36 by fgonzale          #+#    #+#             */
/*   Updated: 2023/04/14 11:44:40 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exit_error(int error_status, t_data *data)
{
	if (data)
	{
		close_fds(data);
		if (data->p_fd)
			free(data->p_fd);
		if (data->cmd_paths)
			free_cmd_paths(data);
		if (data->cmd_args)
			free_cmd_args(data);
		if (data->pid)
			free(data->pid);
	}
	if (data->is_heredoc)
		unlink(".here_doc.tmp");
	exit(error_status);
}

int	msg(char *str, char *str2, char *str3, int error)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
	write(2, "\n", 1);
	return (error);
}
