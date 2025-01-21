/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:36:49 by cwon              #+#    #+#             */
/*   Updated: 2025/01/21 09:33:18 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	safe_execve(t_pipex *param, char *pathname, char **argv)
{
	if (execve(pathname, argv, param->environ) == -1)
	{
		if (errno == EACCES)
			perror_exit(param, "permission denied", 126);
		if (errno == ENOENT)
			perror_exit(param, "command not found", 127);
		flush_exit(param, "execve", EXIT_FAILURE);
	}
}

static void	check_file_permission(t_pipex *param, size_t i)
{
	if (param->file1 && !i && access(param->file1, R_OK) == -1)
		perror_exit(param, param->file1, EXIT_FAILURE);
	if (i == param->cmd_count - 1 && access(param->file2, W_OK) == -1)
		perror_exit(param, param->file2, EXIT_FAILURE);
}

static void	exec_command(t_pipex *param, size_t i, int input_fd, int output_fd)
{
	char	**argv;
	char	*pathname;
	char	*cmd;

	cmd = param->commands[i];
	argv = tokenize(cmd);
	if (!argv)
		flush_exit(param, "tokenize", EXIT_FAILURE);
	deallocate_append_str_array(param, argv);
	pathname = find_command_path(param, argv[0]);
	if (!pathname)
		flush_exit(param, "command not found", 127);
	check_file_permission(param, i);
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
	safe_execve(param, pathname, argv);
}

static pid_t	child_process(t_pipex *param, size_t i, int *pipefd, int prev)
{
	pid_t	pid;

	pid = fork();
	if (pid > 0)
		return (pid);
	if (!pid)
	{
		if (prev != STDIN_FILENO)
		{
			dup2(prev, STDIN_FILENO);
			close(prev);
		}
		if (pipefd[1] != STDOUT_FILENO)
		{
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		if (pipefd[0] != STDIN_FILENO)
			close(pipefd[0]);
		exec_command(param, i, prev, pipefd[1]);
	}
	else
		perror_exit(param, "fork", EXIT_FAILURE);
	return (pid);
}

void	create_pipeline(t_pipex *param)
{
	int		pipefd[2];
	int		prev_fd;
	size_t	i;

	prev_fd = param->file1_fd;
	i = 0;
	while (i < param->cmd_count)
	{
		if (i < param->cmd_count - 1)
		{
			if (pipe(pipefd) == -1)
				perror_exit(param, "pipe", EXIT_FAILURE);
		}
		else
			pipefd[1] = param->file2_fd;
		param->last_pid = child_process(param, i, pipefd, prev_fd);
		if (prev_fd != param->file1_fd)
			close(prev_fd);
		close(pipefd[1]);
		prev_fd = pipefd[0];
		i++;
	}
	if (prev_fd != param->file1_fd)
		close(prev_fd);
}
