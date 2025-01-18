/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:05:42 by cwon              #+#    #+#             */
/*   Updated: 2025/01/18 09:11:46 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

# include "tokenizer.h"

typedef struct s_pipex
{
	char	**commands;
	char	**envp;
	int		file1_fd;
	int		file2_fd;
	int		pipefd[2];
	int		prev_fd;
	size_t	cmd_count;
	t_list	*deallocate;
}	t_pipex;

// flush_pipex.c
void	deallocate_append(t_pipex *param, char **args);
void	error_exit(t_pipex *param, char *s, int status);
void	flush_pipex(t_pipex *param);
void	perror_exit(t_pipex *param, char *s, int status);
void	safe_close(int *fd);

// path.c
char	*find_command_path(char *cmd, char **envp);

// pipex.c
void	pipex(int argc, char **argv, char **envp);

// pipex_util.c
void	create_pipeline(t_pipex *param);

#endif