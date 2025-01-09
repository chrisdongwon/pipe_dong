/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:07:49 by cwon              #+#    #+#             */
/*   Updated: 2025/01/09 14:46:14 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	exec_cmd(t_pipex *param, ssize_t i)
{
	if (!i)
	{
		if (access(param->input_file, R_OK) == -1 && errno == EACCES)
			perror_exit(param, "no read permission on input file", 1);
		protected_dup2(param, param->input_fd, STDIN_FILENO);
	}
	else
	{

	}
	if (i < param->arg_count - 1)
	{

	}
	else
	{
		if (access(param->output_file, W_OK) == -1 && errno == EACCES)
			perror_exit(param, "no write permission on output file", 1);
		protected_dup2(param, param->pipefd[0], STDIN_FILENO);
	}
}

void	pipex(int argc, char **argv)
{
	t_pipex	param;
	ssize_t	i;

	init_pipex(&param, argc, argv);
	i = -1;
	while (++i < param.arg_count)
	{
		protected_pipe(&param);
		param.arg_array[i].pid = protected_fork(&param);
		if (!param.arg_array[i].pid)
			exec_cmd(&param, i);
	}
	flush_pipex(&param);
	i = -1;
	while(++i < param.arg_count)
		param.arg_array[i].pid = waitpid(param.arg_array[i].pid, &param.arg_array[i].status, 0);
	if (WEXITSTATUS(param.arg_array[i].status))
		exit(WEXITSTATUS(param.arg_array[i].status));
}

int	main(int argc, char **argv)
{
	pipex(argc, argv);
	return (0);
}
