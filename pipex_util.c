/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:36:49 by cwon              #+#    #+#             */
/*   Updated: 2025/01/19 13:04:34 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	safe_execve(t_pipex *param, char *cmd_path, char **args)
{
	char	**envp;

	envp = param->environ;
	if (!cmd_path)
		envp = 0;
	if (execve(cmd_path, args, envp) == -1)
	{
		if (errno == EACCES)
			perror_exit(param, "permission denied", 126);
		if (errno == ENOENT)
			perror_exit(param, "command not found", 127);
		perror_exit(param, "execve", EXIT_FAILURE);
	}
}

static void	check_file_permission(t_pipex *param, size_t i)
{
	if (i == 0 && access(param->file1, R_OK) == -1)
		perror_exit(param, param->file1, 1);
	if (i == param->cmd_count - 1 && access(param->file2, W_OK) == -1)
		perror_exit(param, param->file2, 1);
}

static void	exec_command(t_pipex *param, size_t i, int input_fd, int output_fd)
{
	char	**args;
	char	*cmd_path;
	char	*cmd;

	cmd = param->commands[i];
	args = tokenize(cmd);
	if (!args)
		flush_exit(param, "tokenize", EXIT_FAILURE);
	deallocate_append_str_array(param, args);
	cmd_path = find_command_path(param, args[0]);
	if (!cmd_path)
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
	safe_execve(param, cmd_path, args);
}

static void	child_process(t_pipex *param, size_t i, int pipefd[2], int prev_fd)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		if (prev_fd != STDIN_FILENO)
		{
			dup2(prev_fd, STDIN_FILENO);
			close(prev_fd);
		}
		if (pipefd[1] != STDOUT_FILENO)
		{
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		if (pipefd[0] != STDIN_FILENO)
			close(pipefd[0]);
		exec_command(param, i, prev_fd, pipefd[1]);
	}
	else if (pid == -1)
		perror_exit(param, "fork", EXIT_FAILURE);
	else
		param->pid_array[i] = pid;
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
		child_process(param, i, pipefd, prev_fd);
		if (prev_fd != param->file1_fd)
			close(prev_fd);
		close(pipefd[1]);
		prev_fd = pipefd[0];
		i++;
	}
	if (prev_fd != param->file1_fd)
		close(prev_fd);
}
