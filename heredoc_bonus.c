/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:14:14 by cwon              #+#    #+#             */
/*   Updated: 2025/01/20 22:21:23 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_heredoc(t_pipex *param, int argc, char **argv)
{
	char	*limiter;
	char	*line;
	int		pipefd[2];
	size_t	len;

	limiter = argv[2];
	if (pipe(pipefd) == -1)
		perror_exit(param, "pipe", EXIT_FAILURE);
	len = ft_strlen(limiter);
	while (get_next_line(STDIN_FILENO, &line) && line)
	{
		if (!ft_strncmp(line, limiter, len) && line[len] == '\n')
			break ;
		write(pipefd[1], line, ft_strlen(line));
		free(line);
		line = 0;
	}
	if (line)
		free(line);
	close(pipefd[1]);
	param->file1_fd = pipefd[0];
	param->file2_fd = \
	open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
}
