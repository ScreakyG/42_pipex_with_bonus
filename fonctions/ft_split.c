/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:42:33 by francois          #+#    #+#             */
/*   Updated: 2023/04/05 17:32:26 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static size_t	ft_countwords(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static size_t	ft_words_len(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	ft_free_split(char **tabtab, unsigned int nb)
{
	unsigned int	index;

	index = 0;
	while (index < nb)
	{
		free(tabtab[index]);
		index++;
	}
	free(tabtab);
}

char	**ft_split(char const *s, char c)
{
	size_t	words_total;
	size_t	words_len;
	size_t	i;
	char	**tabtab;

	if (!s)
		return (0);
	i = 0;
	words_total = ft_countwords(s, c);
	tabtab = malloc((words_total + 1) * sizeof(char *));
	if (!tabtab)
		return (0);
	while (i < words_total)
	{
		words_len = ft_words_len(s, c);
		if (words_len > 0)
		{
			tabtab[i] = ft_substr(s, 0, words_len);
			if (!tabtab[i++])
				return (ft_free_split(tabtab, i), NULL);
		}
		s = &s[words_len + 1];
	}
	tabtab[words_total] = NULL;
	return (tabtab);
}
