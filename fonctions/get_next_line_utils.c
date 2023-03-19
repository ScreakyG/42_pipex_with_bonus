/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 18:58:39 by fgonzale          #+#    #+#             */
/*   Updated: 2023/03/16 07:42:35 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_check_line(char *saved)
{
	if (!saved)
		return (0);
	while (*saved)
	{
		if (*saved == '\n')
			return (1);
		saved++;
	}
	return (0);
}

char	*ft_strjoin2(char *saved, char *buffer)
{
	char			*join;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	join = malloc((ft_strlen(saved) + ft_strlen(buffer) + 1) * sizeof(char));
	if (!join)
		return (NULL);
	if (saved != NULL)
	{
		while (saved[i])
		{
			join[i] = saved[i];
			i++;
		}
	}
	while (buffer[j])
		join [i++] = buffer[j++];
	join[i] = '\0';
	free(saved);
	return (join);
}

char	*cut_at_line(char *saved)
{
	char			*line;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (saved[0] == '\0')
		return (NULL);
	while (saved[i] && saved[i] != '\n')
		i++;
	if (saved[i] == '\n')
		i++;
	line = malloc ((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = saved[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*clean_at_line(char *saved)
{
	unsigned int	i;
	unsigned int	j;
	char			*cleaned;

	i = 0;
	j = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (saved[i] == '\0')
	{
		free(saved);
		return (NULL);
	}
	i++;
	cleaned = malloc((ft_strlen(saved) - i + 1) * sizeof(char));
	if (!cleaned)
		return (NULL);
	while (saved[i] != '\0')
		cleaned[j++] = saved[i++];
	cleaned[j] = '\0';
	free(saved);
	return (cleaned);
}
