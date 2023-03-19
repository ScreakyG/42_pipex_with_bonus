/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 01:41:24 by fgonzale          #+#    #+#             */
/*   Updated: 2023/03/15 02:02:16 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->nb_cmds - 1) * 2)
	{
		close(data->pipe_fd[i]);
		i++;
	}
}

char	*get_paths_envp(char **envp)
{
	while (ft_strncmp(*envp, "PATH", 4))
		envp++;
	return (*envp + 5);
}

char	*get_cmd(char **cmd_paths, char *cmd_args)
{
	char	*cmd;
	char	*temp;

	while (*cmd_paths) // PROBLEEME AVEC VALGRIND QUI STOP PAS
	{
		temp = ft_strjoin(*cmd_paths, "/");
		cmd = ft_strjoin(temp, cmd_args);
		free(temp);
		if (access(cmd, 0) == 0)
			return (cmd);
		free(cmd);
		cmd_paths++;
	}
	return (NULL);
}
