/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:57:37 by cwon              #+#    #+#             */
/*   Updated: 2025/01/19 12:58:57 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	validate_args(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("Usage:\t./pipex file1 cmd1 cmd2 file2\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

static void	init_pipex(t_pipex *param, int argc, char **argv, char **envp)
{
	size_t	i;

	param->deallocate = 0;
	param->environ = envp;
	param->file1 = argv[1];
	param->file1_fd = open(argv[1], O_RDONLY);
	param->file2 = argv[argc - 1];
	param->file2_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	param->cmd_count = argc - 3;
	param->commands = (char **)malloc(param->cmd_count * sizeof(char *));
	param->pid_array = (pid_t *)malloc(param->cmd_count * sizeof(pid_t));
	if (!param->commands | !param->pid_array)
		perror_exit(param, "malloc", EXIT_FAILURE);
	i = 0;
	while (i < param->cmd_count)
	{
		param->commands[i] = argv[i + 2];
		i++;
	}
	param->commands[i] = 0;
}

static void	wait_for_children(t_pipex *param)
{
	int		status;
	int		exit_status;
	size_t	i;
	pid_t	pid;

	ft_printf("child pids:\n");
	for (size_t i = 0; i < param->cmd_count; i++)
		ft_printf("child %ld: %d\n", i, param->pid_array[i]);

	exit_status = 0;
	i = 0;
	while (i < param->cmd_count)
	{
		pid = wait(&status);
		if (status && !exit_status)
			exit_status = status;
		ft_printf("exit status of process %ld of pid %d: %d\n", i, pid, WEXITSTATUS(status));
		i++;
	}
	exit(WEXITSTATUS(exit_status));
}

void	pipex(int argc, char **argv, char **envp)
{
	t_pipex	param;

	validate_args(argc);
	init_pipex(&param, argc, argv, envp);
	create_pipeline(&param);
	flush_pipex(&param);
	wait_for_children(&param);
}

int	main(int argc, char **argv, char **envp)
{
	pipex(argc, argv, envp);
	return (0);
}
