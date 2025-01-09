/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_process_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:30:24 by cwon              #+#    #+#             */
/*   Updated: 2025/01/09 12:41:57 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	protected_pipe(t_pipex *param)
{
	if (pipe(param->pipefd) == -1)
		perror_exit(param, "pipe failed", EXIT_FAILURE);
}

pid_t	protected_fork(t_pipex *param)
{
	pid_t	result;

	result = fork();
	if (result == -1)
		perror_exit(param, "fork failed", EXIT_FAILURE);
	return (result);
}

void	protected_execve(t_pipex *param, char *pathname, char **argv)
{
	char	**environment;

	environment = environ;
	if (!param->envp)
		environment = 0;
	if (execve(pathname, argv, environment) == -1)
	{
		if (errno == EACCES)
			perror_exit(param, "Permission denied", 126);
		if (errno == ENOENT)
			perror_exit(param, "command not found", 127);
		perror_exit(param, "execve failed", EXIT_FAILURE);
	}
}
