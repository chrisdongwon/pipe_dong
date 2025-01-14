/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:07:47 by cwon              #+#    #+#             */
/*   Updated: 2025/01/13 15:47:14 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

# include "tokenizer.h"

typedef struct s_pipex
{
	char	**env_paths;
	char	**environ;
	char	*file1;
	char	*file2;
	char	*limiter;
	int		here_doc;
	int		last_status;
	size_t	cmd_count;
	t_list	*commands;
}	t_pipex;

// pipex_bonus.c
void	pipex(int argc, char **argv, char **envp);

// init_bonus.c
void	init_pipex(t_pipex *param, int argc, char **argv, char **envp);

#endif