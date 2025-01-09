/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:44:57 by cwon              #+#    #+#             */
/*   Updated: 2025/01/09 12:58:36 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

# include "libft/libft.h"

extern char	**environ;

typedef struct s_arg
{
	char	**cmd;
	char	*path;
	pid_t	pid;
	int		status;
}	t_arg;

typedef struct s_pipex
{
	char	**envp;
	int		pipefd[2];

	char	*input_file;
	char	*output_file;
	int		input_fd;
	int		output_fd;

	ssize_t	arg_count;
	t_arg	*arg_array;
}	t_pipex;

typedef struct s_tokenizer
{
	char	*str;
	size_t	len;
	size_t	i;
	size_t	j;
	int		single_quote;
	int		double_quote;
}	t_tokenizer;

// pipex_bonus.c
void	pipex(int argc, char **argv);

// init_bonus.c
void	init_pipex(t_pipex *param, int argc, char **argv);

// tokenizer_bonus.c
char	**tokenize(t_pipex *param, char *cmd);

// tokenizer_util_bonus.c
void	init_tokenizer(t_list **node, t_tokenizer *data, char *input);
void	append_token(t_list **head, char *token);
char	**list_to_array(t_list *node);
int		whitespace_command(char *str);

// protect_process_bonus.c
void	protected_pipe(t_pipex *param);
pid_t	protected_fork(t_pipex *param);
void	protected_execve(t_pipex *param, char *pathname, char **argv);

// protect_file_bonus.c
int		protected_open(char *pathname, int flags);
void	protected_close(int *fd);
void	protected_dup2(t_pipex *param, int oldfd, int newfd);

// protect_string_bonus.c
char	**protected_split(t_pipex *param, char *str, char c);
char	*protected_strjoin(t_pipex *param, char *s1, char *s2);
char	*protected_strdup(t_pipex *param, char *str);
char	*protected_substr(t_pipex *param, char *str, size_t start, size_t len);

// flush_bonus.c
void	flush_pipex(t_pipex *param);
void	*flush_str_array(char **arr);

// error_bonus.c
void	error_exit(t_pipex *param, char *message, int exit_code);
void	perror_exit(t_pipex *param, char *message, int exit_code);

#endif