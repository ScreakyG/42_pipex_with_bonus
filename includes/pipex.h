/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:55:49 by fgonzale          #+#    #+#             */
/*   Updated: 2023/03/16 07:46:11 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_data
{
	int		is_heredoc;
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
int		ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin2(char *saved, char *buffer);

// GET_NEXT_LINE

char	*find_next_line(char *saved, int fd);
char	*get_next_line(int fd);
int		ft_check_line(char *saved);
char	*cut_at_line(char *saved);
char	*clean_at_line(char *saved);

// FILE MANAGER

void	get_infile(t_data *data, char **argv);
void	get_outfile(t_data *data, char **argv, int argc);
void	get_here_doc(char **argv);

// CHILD

void	child_process(t_data data, char **argv, char **envp);

// UTILS

void	close_pipes(t_data *data);
char	*get_paths_envp(char **envp);
char	*get_cmd(char **cmd_paths, char *cmd_args);
void	make_pipes(t_data *data);

// FREE

void	free_only_pipe(t_data *data);
void	free_parent_data(t_data *data);
void	free_child_data(t_data *data);

// ERROR_MSG

void	msg_error(char *str);

#endif
