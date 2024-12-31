/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:16:24 by cwon              #+#    #+#             */
/*   Updated: 2024/12/29 14:04:04 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_cmd1(t_pipex *param)
{
	if (access(param->input_file, R_OK) == -1 && errno == EACCES)
		perror_exit(param, "no read permission on input file", 1);
	protected_dup2(param, param->input_fd, STDIN_FILENO);
	protected_dup2(param, param->pipefd[1], STDOUT_FILENO);
	protected_close(&(param->pipefd[0]));
	protected_execve(param, param->path1, param->cmd1);
}

static void	exec_cmd2(t_pipex *param)
{
	if (access(param->output_file, W_OK) == -1 && errno == EACCES)
		perror_exit(param, "no write permission on output file", 1);
	protected_dup2(param, param->pipefd[0], STDIN_FILENO);
	protected_dup2(param, param->output_fd, STDOUT_FILENO);
	protected_close(&(param->pipefd[1]));
	protected_execve(param, param->path2, param->cmd2);
}

void	pipex(int argc, char **argv)
{
	t_pipex	param;

	init_pipex(&param, argc, argv);
	param.pid1 = protected_fork(&param);
	if (!param.pid1)
		exec_cmd1(&param);
	param.pid2 = protected_fork(&param);
	if (!param.pid2)
		exec_cmd2(&param);
	flush_pipex(&param);
	param.pid1 = waitpid(param.pid1, &param.status1, 0);
	param.pid2 = waitpid(param.pid2, &param.status2, 0);
	if (WEXITSTATUS(param.status2))
		exit(WEXITSTATUS(param.status2));
}

int	main(int argc, char **argv)
{
	pipex(argc, argv);
	return (0);
}
