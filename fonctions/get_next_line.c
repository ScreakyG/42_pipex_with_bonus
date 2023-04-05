/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 02:42:51 by fgonzale          #+#    #+#             */
/*   Updated: 2023/04/05 17:39:16 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*get_before_line(char *temp)
{
	char			*line;
	unsigned int	i;

	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (temp[i] && temp[i] != '\n')
	{
		line[i] = temp[i];
		i++;
	}
	if (temp[i] == '\n')
	{
		line[i] = temp[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*get_after_line(char *temp)
{
	char	*new_saved;
	int		size;
	int		i;
	int		j;

	j = 0;
	i = 0;
	size = ft_strlen(temp);
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] != '\0' && temp[i] == '\n')
		i++;
	new_saved = malloc((size - i + 1) * sizeof(char));
	if (!new_saved)
		return (NULL);
	while (temp[i])
	{
		new_saved[j] = temp[i];
		i++;
		j++;
	}
	new_saved[j] = '\0';
	return (new_saved);
}

static char	*get_lines(char **saved, char **temp)
{
	char	*line;

	*temp = ft_strdup(*saved);
	ft_free(saved, NULL, NULL);
	line = get_before_line(*temp);
	*saved = get_after_line(*temp);
	ft_free(temp, NULL, NULL);
	return (line);
}

static void	read_lines(int fd, char **saved, char **temp)
{
	int		readed_bytes;
	char	*buffer;

	readed_bytes = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		ft_free(saved, temp, NULL);
		return ;
	}
	while (readed_bytes != 0 && !ft_strchr(*saved, '\n'))
	{
		readed_bytes = read(fd, buffer, BUFFER_SIZE);
		if (readed_bytes == -1)
		{
			ft_free(saved, temp, &buffer);
			return ;
		}
		buffer[readed_bytes] = '\0';
		*temp = ft_strdup(*saved);
		ft_free(saved, NULL, NULL);
		*saved = ft_join_str(*temp, buffer);
		ft_free(temp, NULL, NULL);
	}
	ft_free(temp, &buffer, NULL);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*temp;
	char		*line;

	temp = NULL;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		ft_free(&saved, &temp, &line);
		return (NULL);
	}
	read_lines(fd, &saved, &temp);
	if (saved && *saved != '\0')
		line = get_lines(&saved, &temp);
	if (!line || *line == '\0')
	{
		ft_free(&saved, &temp, &line);
		return (NULL);
	}
	return (line);
}
