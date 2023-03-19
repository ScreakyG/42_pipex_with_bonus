/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 06:11:52 by fgonzale          #+#    #+#             */
/*   Updated: 2023/03/19 03:51:55 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_here_doc(char **argv)
{
	char	*line;
	int		temp_fd;

	temp_fd = open(".here_doc.tmp", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (temp_fd < 0)
		msg_error("Error while opening HERE_DOC fd ");

	while (1)
	{
		ft_putstr_fd("heredoc > ", 1);
		line = get_next_line(0);
		if (line == NULL)
			exit(1);
		if (ft_strlen(argv[2]) + 1 == ft_strlen(line) && !ft_strncmp(argv[2], line, ft_strlen(argv[2])))
			break;
		ft_putstr_fd(line, temp_fd);
		free(line);
	}
	free(line);
	close(temp_fd);
}
