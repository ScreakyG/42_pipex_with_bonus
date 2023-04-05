/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:54:31 by fgonzale          #+#    #+#             */
/*   Updated: 2023/03/19 07:03:59 by fgonzale         ###   ########.fr       */
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
			exit_error(msg("Error pipeline", ": ", 1), data);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc < 5)
		return (msg("Wrong argument count\n", "", 1));
	if (argc == 5)
	{
		if (!ft_strncmp("here_doc", argv[1], 9))
			return (msg("You need to add LIMITER\n", "", 1));
	}
	get_infile(&data, argv);
	get_outfile(&data, argv, argc);
	data.nb_cmds = (argc - 3 - data.is_heredoc);
	data.pipe_fd = malloc(((data.nb_cmds - 1) * 2) * sizeof(int));
	if (!data.pipe_fd)
		exit_error(msg("Error with pipes", ": ", 1), &data);
	data.paths_envp = get_paths_envp(envp);
	data.cmd_paths = ft_split(data.paths_envp, ':');
	if (!data.cmd_paths)
		exit_error(msg("Error with cmd_paths", ": ", 1), &data);
	make_pipes(&data);
	data.index = 0;
	while (data.index < data.nb_cmds)
	{
		child_process(data, argv, envp);
		data.index++;
	}
	free_parent(&data);
	waitpid(-1, NULL, 0);
	return (0);
}
