/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:46:02 by cwon              #+#    #+#             */
/*   Updated: 2025/01/18 09:11:08 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	deallocate_path(t_pipex *param, char *cmd_path)
{
	t_list	*node;

	node = ft_lstnew(cmd_path);
	if (!node)
	{
		free(cmd_path);
		error_exit(param, "lstnew", EXIT_FAILURE);
	}
	ft_lstadd_back(&(param->deallocate), node);
}

static void	execute_command(t_pipex *param, char *cmd, int *in_fd, int *out_fd)
{
	char	**args;
	char	*cmd_path;

	args = tokenize(cmd);
	if (!args)
		error_exit(param, "tokenize", EXIT_FAILURE);
	deallocate_append(param, args);
	cmd_path = find_command_path(args[0], param->envp);
	if (!cmd_path)
		error_exit(param, "find_command_path", EXIT_FAILURE);
	deallocate_path(param, cmd_path);
	if (*in_fd != STDIN_FILENO)
	{
		dup2(*in_fd, STDIN_FILENO);
		safe_close(in_fd);
	}
	if (*out_fd != STDOUT_FILENO)
	{
		dup2(*out_fd, STDOUT_FILENO);
		safe_close(out_fd);
	}
	if (execve(cmd_path, args, param->envp) == -1)
		perror_exit(param, "execve", EXIT_FAILURE);
}

static void	child_process(t_pipex *param, size_t i)
{
	char	*cmd;

	cmd = param->commands[i];
	if (param->prev_fd != STDIN_FILENO && param->prev_fd != -1)
	{
		dup2(param->prev_fd, STDIN_FILENO);
		safe_close(&(param->prev_fd));
	}
	if (param->pipefd[1] != STDOUT_FILENO && param->pipefd[1] != -1)
	{
		dup2(param->pipefd[1], STDOUT_FILENO);
		safe_close(&(param->pipefd[1]));
	}
	if (param->pipefd[0] != STDIN_FILENO)
		safe_close(&(param->pipefd[0]));
	execute_command(param, cmd, &(param->prev_fd), &(param->pipefd[1]));
}

void	create_pipeline(t_pipex *param)
{
	pid_t	pid;
	size_t	i;

	param->prev_fd = param->file1_fd;
	i = 0;
	while (i < param->cmd_count)
	{
		if ((i < param->cmd_count - 1) && (pipe(param->pipefd) == -1))
			perror_exit(param, "pipe", EXIT_FAILURE);
		else
			param->pipefd[1] = param->file2_fd;
		pid = fork();
		if (pid == -1)
			perror_exit(param, "fork", EXIT_FAILURE);
		if (!pid)
			child_process(param, i);
		if (param->prev_fd != param->file1_fd)
			safe_close(&(param->prev_fd));
		safe_close(&(param->pipefd[1]));
		param->prev_fd = param->pipefd[0];
		i++;
	}
	if (param->prev_fd != param->file1_fd)
		safe_close(&(param->prev_fd));
}
