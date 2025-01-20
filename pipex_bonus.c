/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:07:05 by cwon              #+#    #+#             */
/*   Updated: 2025/01/20 22:20:25 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	validate_args(int argc, char **argv)
{
	if (argc < 5 || (!ft_strncmp(argv[1], "here_doc", 9) && argc < 6))
	{
		ft_putstr_fd \
		("Usage:\t./pipex file1 cmd1 cmd2 ... <cmd_n> file2\n", 2);
		ft_putstr_fd \
		("\t./pipex here_doc LIMITER cmd cmd1 ... <cmd_n> file\n", 2);
		exit(EXIT_FAILURE);
	}
}

static void	init_pipex(t_pipex *param, int argc, char **argv, char **envp)
{
	size_t	i;

	param->deallocate = 0;
	param->environ = envp;
	param->heredoc = !ft_strncmp(argv[1], "here_doc", 9);
	if (param->heredoc)
		init_heredoc(param, argc, argv);
	else
	{
		param->file1 = argv[1];
		param->file1_fd = open(argv[1], O_RDONLY);
		param->file2_fd = \
		open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	param->file2 = argv[argc - 1];
	param->cmd_count = argc - 3 - param->heredoc;
	param->env_path = init_env_path(param);
	param->commands = (char **)malloc(param->cmd_count * sizeof(char *));
	if (!param->commands)
		perror_exit(param, "malloc", EXIT_FAILURE);
	i = -1;
	while (++i < param->cmd_count)
		param->commands[i] = argv[i + 2 + param->heredoc];
}

static void	wait_for_children(t_pipex *param)
{
	int		status;
	int		exit_status;
	size_t	i;
	pid_t	pid;

	exit_status = 0;
	i = 0;
	while (i < param->cmd_count)
	{
		pid = wait(&status);
		if (pid == param->last_pid)
			exit_status = status;
		i++;
	}
	exit(WEXITSTATUS(exit_status));
}

void	pipex(int argc, char **argv, char **envp)
{
	t_pipex	param;

	validate_args(argc, argv);
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
