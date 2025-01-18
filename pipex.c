/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 08:16:36 by cwon              #+#    #+#             */
/*   Updated: 2025/01/18 09:10:09 by cwon             ###   ########.fr       */
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

	validate_args(argc);
	param->envp = envp;
	param->file1_fd = open(argv[1], O_RDONLY);
	param->file2_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_memset(param->pipefd, -1, 2);
	param->prev_fd = -1;
	param->deallocate = 0;
	param->cmd_count = argc - 3;
	param->commands = (char **)malloc((param->cmd_count + 1) * sizeof(char *));
	if (!param->commands)
		perror_exit(param, "malloc", EXIT_FAILURE);
	i = 0;
	while (i < param->cmd_count)
	{
		param->commands[i] = argv[i + 2];
		i++;
	}
	param->commands[i] = 0;
}

void	pipex(int argc, char **argv, char **envp)
{
	t_pipex	param;

	init_pipex(&param, argc, argv, envp);
	create_pipeline(&param);
	flush_pipex(&param);
}

int	main(int argc, char **argv, char **envp)
{
	pipex(argc, argv, envp);
	return (0);
}
