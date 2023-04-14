/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:54:31 by fgonzale          #+#    #+#             */
/*   Updated: 2023/04/14 11:42:26 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	make_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds - 1)
	{
		if (pipe(data->p_fd + 2 * i) == -1)
			exit_error(msg(ERR_PIPES, "", "", 1), data);
		i++;
	}
}

int	exit_code(t_data *data)
{
	int		exit_code;
	int		status;
	pid_t	compare_pid;

	close_fds(data);
	exit_code = 1;
	data->i--;
	while (data->i >= 0)
	{
		compare_pid = waitpid(data->pid[data->i], &status, 0);
		if (compare_pid == data->pid[data->nb_cmds - 1])
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
		}
		data->i--;
	}
	free_parent(data);
	return (exit_code);
}

static void	init_data(t_data *data, int argc, char **argv, char **envp)
{
	get_infile(data, argv);
	get_outfile(data, argv, argc);
	data->nb_cmds = (argc - 3 - data->is_heredoc);
	data->p_fd = malloc(((data->nb_cmds - 1) * 2) * sizeof(int));
	if (!data->p_fd)
		exit_error(msg(ERR_PIPES, "", "", 1), data);
	data->paths_envp = get_paths_envp(envp);
	data->cmd_paths = ft_split(data->paths_envp, ':');
	if (!data->cmd_paths)
		exit_error(msg(ERR_PATHS, "", "", 1), data);
	data->pid = malloc(data->nb_cmds * sizeof(int));
	if (!data->pid)
		exit_error(msg(ERR_PIDS, "", "", 1), data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc < 5)
		return (msg(ERR_ARGS, "", "", 1));
	if (argc == 5)
	{
		if (!ft_strncmp("here_doc", argv[1], 9))
			return (msg("You need to add LIMITER\n", "", "", 1));
	}
	init_data(&data, argc, argv, envp);
	make_pipes(&data);
	data.i = 0;
	while (data.i < data.nb_cmds)
	{
		child_process(data, argv, envp);
		data.i++;
	}
	return (exit_code(&data));
}
