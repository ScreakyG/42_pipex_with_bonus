/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 06:11:52 by fgonzale          #+#    #+#             */
/*   Updated: 2023/03/19 03:06:34 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_here_doc(char **argv)
{
	char	*line;
	int		std_input_dup;
	int		temp_fd;

	std_input_dup = dup(STDIN_FILENO);
	temp_fd = open(".here_doc.tmp", O_CREAT | O_TRUNC | O_WRONLY, 0644);

	line = "";
	while (1)
	{
		ft_putstr_fd("here_doc > ", 1);
		line = get_next_line(std_input_dup); //
		if (line == NULL)
			break;
		if (!ft_strncmp(line, argv[2], ft_strlen(argv[2]) + 1)) /// IL FAUT VERIFIER AVEC STRLEN
			close(std_input_dup);
		else
			ft_putstr_fd(line, temp_fd); //
		free(line);
	}
	close(temp_fd);
}
