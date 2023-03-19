/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:53:18 by fgonzale          #+#    #+#             */
/*   Updated: 2023/03/16 06:30:49 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(t_data data, char **argv, char **envp)
{
	data.pid = fork();
	if (data.pid == 0)
	{
		if (data.index == 0)
		{
			dup2(data.infile, 0);
			dup2(data.pipe_fd[1], 1);
		}
		else if (data.index == data.nb_cmds - 1) // Si j'ai 3 cmds mon dernier index sera 2.
		{
			dup2(data.outfile, 1);
			dup2(data.pipe_fd[data.index * 2 - 2], 0);
		}
		else
		{
			dup2(data.pipe_fd[data.index * 2 - 2], 0);
			dup2(data.pipe_fd[data.index * 2 + 1], 1);
		}
		close_pipes(&data);
		data.cmd_args = ft_split(argv[2 + data.index + data.is_heredoc], ' ');
		data.cmd = get_cmd(data.cmd_paths, data.cmd_args[0]);
		if (!data.cmd)
		{
			free_child_data(&data); // A FAIRE
			msg_error("Error with cmd input : ");
		}
		execve(data.cmd, data.cmd_args, envp);
	}
}
