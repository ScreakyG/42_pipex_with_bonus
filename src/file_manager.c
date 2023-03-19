/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 05:29:50 by fgonzale          #+#    #+#             */
/*   Updated: 2023/03/19 04:06:18 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_infile(t_data *data, char **argv)
{
	if(!ft_strncmp(argv[1], "here_doc", 9))
	{
		get_here_doc(argv);
		data->is_heredoc = 1;
		data->infile = open(".here_doc.tmp", O_RDONLY);
		if (data->infile < 0)
		{
			unlink(".here_doc.tmp");
			msg_error("Error while opening HERE_DOC fd ");
		}
	}
	else
	{
		data->infile = open(argv[1], O_RDONLY, 0644);
		if (data->infile < 0)
			msg_error("Error while opening INFILE fd ");
	}
}

void	get_outfile(t_data *data, char **argv, int argc)
{
	if (data->is_heredoc == 1)
		data->outfile = open(argv[argc - 1], O_CREAT | O_APPEND | O_RDWR, 0644);
	else
		data->outfile = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (data->outfile < 0)
		msg_error("Error while opening OUTFILE fd");
}
