/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:53:18 by fgonzale          #+#    #+#             */
/*   Updated: 2023/04/14 11:48:18 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	s_io(int input, int output, t_data *data)
{
	if (dup2(input, 0) == -1)
		exit_error(1, data);
	if (dup2(output, 1) == -1)
		exit_error(1, data);
}

void	child_process(t_data data, char **argv, char **envp)
{
	data.pid[data.i] = fork();
	if (data.pid[data.i] == 0)
	{
		data.cmd_args = NULL;
		if (data.i == 0)
			s_io(data.infile, data.p_fd[1], &data);
		else if (data.i == data.nb_cmds - 1)
			s_io(data.p_fd[data.i * 2 - 2], data.outfile, &data);
		else
			s_io(data.p_fd[data.i * 2 - 2], data.p_fd[data.i * 2 + 1], &data);
		close_fds(&data);
		data.cmd_args = ft_split(argv[2 + data.i + data.is_heredoc], ' ');
		data.cmd = get_cmd(data.cmd_paths, data.cmd_args[0]);
		if (!data.cmd)
			exit_error(msg(ERR_CMD, data.cmd_args[0], "", 127), &data);
		if (execve(data.cmd, data.cmd_args, envp) == -1)
			exit_error(msg(data.cmd_args[0], strerror(errno), "", 1), &data);
	}
}
