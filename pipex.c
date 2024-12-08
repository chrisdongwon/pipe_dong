/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:31:26 by cwon              #+#    #+#             */
/*   Updated: 2024/12/08 11:53:31 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute_process(char *command)
{
	int		status;
	char	**argv;
	char	*pathname;

	status = 0;
	argv = parse_command(command);
	if (!argv)
		exit(EXIT_FAILURE);
	pathname = get_pathname(argv);
	status = execve(pathname, argv, environ);
	flush_str_array(argv);
	free(pathname);
	if (status == -1)
	{
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
}

static void	parent_process(char *argv[], int pipefd[2])
{
	int	fd;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	execute_process(argv[3]);
}

static void	child_process(char *argv[], int pipefd[2])
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	execute_process(argv[2]);
}

void	pipex(int argc, char *argv[])
{
	int		pipefd[2];
	pid_t	pid;

	if (argc != 5 || pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
		child_process(argv, pipefd);
	parent_process(argv, pipefd);
}
