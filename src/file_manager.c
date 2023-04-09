/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 05:29:50 by fgonzale          #+#    #+#             */
/*   Updated: 2023/04/09 23:35:11 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_infile(t_data *data, char **argv)
{
	data->is_heredoc = 0;
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		get_here_doc(argv, data);
		data->is_heredoc = 1;
		data->infile = open(".here_doc.tmp", O_RDONLY);
		if (data->infile < 0)
			exit_error(msg("here_doc", ": ", "", 1), data);
	}
	else
		data->infile = open(argv[1], O_RDONLY, 0644);
	if (data->infile < 0)
		msg(strerror(errno), " : ", argv[1], 1);
}

void	get_outfile(t_data *data, char **argv, int argc)
{
	if (data->is_heredoc == 1)
		data->outfile = open(argv[argc - 1], O_CREAT | O_APPEND | O_RDWR, 0644);
	else
		data->outfile = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (data->outfile < 0)
		msg(strerror(errno), " : ", "", 1);
}
