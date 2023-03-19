/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:54:31 by fgonzale          #+#    #+#             */
/*   Updated: 2023/03/19 03:10:44 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	make_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds - 1)
	{
		if (pipe(data->pipe_fd + 2 * i) == -1)
		{
			free_parent_data(data);
			msg_error("Error creating pipes : ");
		}
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	get_infile(&data, argv);
	get_outfile(&data, argv, argc);
	if (data.infile < 0 || data.outfile < 0)
		msg_error("Error while creating FDs : "); // A REFAIRE EN GERANT HERE_DOC
	data.nb_cmds = (argc - 3 - data.is_heredoc);
	data.pipe_fd = malloc(((data.nb_cmds - 1) * 2) * sizeof(int));
	if (!data.pipe_fd)
		msg_error("Malloc pipe error : ");
	data.paths_envp = get_paths_envp(envp);
	data.cmd_paths = ft_split(data.paths_envp, ':');
	if (!data.cmd_paths)
	{
		free_only_pipe(&data);
		msg_error("Error with cmd_paths : "); // A REFAIRE
	}
	make_pipes(&data);
	data.index = 0;
	while (data.index < data.nb_cmds)
	{
		child_process(data, argv, envp);
		data.index++;
	}
	close_pipes(&data);
	waitpid(-1, NULL, 0);
	free_parent_data(&data);
	return (0);
}
