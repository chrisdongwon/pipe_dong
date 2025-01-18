/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:57:37 by cwon              #+#    #+#             */
/*   Updated: 2025/01/18 13:11:25 by cwon             ###   ########.fr       */
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

	validate_args(argc);
	init_pipex(&param, argc, argv, envp);
	create_pipeline(&param);
	while (wait(0) > 0)
		continue ;
	flush_pipex(&param);
}

int	main(int argc, char **argv, char **envp)
{
	pipex(argc, argv, envp);
	return (0);
}
