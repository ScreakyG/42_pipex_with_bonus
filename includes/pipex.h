/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:55:49 by fgonzale          #+#    #+#             */
/*   Updated: 2023/03/12 23:32:49 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_data
{
	int		index;
	int		pid;
	int		infile;
	int		outfile;
	int		*pipe_fd;
	char	*paths_envp;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
	int		nb_cmds;
} 	t_data;

// FONCTIONS

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);

// CHILD

void	child_process(t_data data, char **argv, char **envp);

// UTILS

void	close_pipes(t_data *data);
char	*get_paths_envp(char **envp);
char	*get_cmd(char **cmd_paths, char **cmd_args);
void	make_pipes(t_data *data);

// FREE

void	free_only_pipe(t_data *data);
void	free_parent_data(t_data *data);
void	free_child_data(t_data *data);

// ERROR_MSG

void	msg_error(char *str);

#endif
