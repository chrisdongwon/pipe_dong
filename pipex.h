/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:05:42 by cwon              #+#    #+#             */
/*   Updated: 2025/01/20 15:07:01 by cwon             ###   ########.fr       */
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
	char	**env_path;
	char	**environ;
	char	*file1;
	char	*file2;
	int		file1_fd;
	int		file2_fd;
	int		heredoc;
	pid_t	last_pid;
	size_t	cmd_count;
	t_list	*deallocate;
}	t_pipex;

// heredoc_bonus.c
void	init_heredoc(t_pipex *param, int argc, char **argv);

// pipex.c
void	pipex(int argc, char **argv, char **envp);

// pipex_path.c
char	**init_env_path(t_pipex *param);
char	*find_command_path(t_pipex *param, char *cmd);

// pipex_util.c
void	create_pipeline(t_pipex *param);

// pipex_flush.c
void	deallocate_append_str_array(t_pipex *param, char **arr);
void	deallocate_append(t_pipex *param, void *ptr);
void	flush_exit(t_pipex *param, char *error_message, int status);
void	flush_pipex(t_pipex *param);
void	perror_exit(t_pipex *param, char *s, int status);

#endif