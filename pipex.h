/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:16:22 by cwon              #+#    #+#             */
/*   Updated: 2024/12/30 18:52:12 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

# include "libft/libft.h"

extern char	**environ;

typedef struct s_pipex
{
	char	**envp;
	int		pipefd[2];
	char	*input_file;
	char	*output_file;
	int		input_fd;
	int		output_fd;

	char	**cmd1;
	char	*path1;
	pid_t	pid1;
	int		status1;

	char	**cmd2;
	char	*path2;
	pid_t	pid2;
	int		status2;
}	t_pipex;

// pipex.c
void	pipex(int argc, char **argv);

// init.c
void	init_pipex(t_pipex *param, int argc, char **argv);

// init_util.c
char	*potential_path(t_pipex *param, char *dir, char *cmd);

// command.c
char	**tokenize(t_pipex *param, char *cmd);

// protect_process.c
void	protected_pipe(t_pipex *param);
pid_t	protected_fork(t_pipex *param);
void	protected_execve(t_pipex *param, char *pathname, char **argv);

// protect_file.c
int		protected_open(char *pathname, int flags);
void	protected_close(int *fd);
void	protected_dup2(t_pipex *param, int oldfd, int newfd);

// protect_string.c
char	**protected_split(t_pipex *param, char *str, char c);
char	*protected_strjoin(t_pipex *param, char *s1, char *s2);
char	*protected_strdup(t_pipex *param, char *str);
char	*protected_substr(t_pipex *param, char *str, size_t start, size_t len);

// flush.c
void	flush_str_array(char **arr);
void	flush_pipex(t_pipex *param);

// error.c
void	error_exit(t_pipex *param, char *message, int exit_code);
void	perror_exit(t_pipex *param, char *message, int exit_code);

#endif