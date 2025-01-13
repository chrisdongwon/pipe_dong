/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:07:56 by cwon              #+#    #+#             */
/*   Updated: 2025/01/13 14:31:00 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	protected_open(char *pathname, int flags)
{
	int	fd;

	if (flags == (O_WRONLY | O_CREAT | O_TRUNC))
	{
		fd = open(pathname, flags, 0644);
		if (fd == -1)
			perror("open");
	}
	else
	{
		fd = open(pathname, flags);
		if (fd == -1)
			perror("open");
	}
	return (fd);
}

void	protected_close(int *fd)
{
	if (*fd != -1)
	{
		if (close(*fd) == -1)
			perror("close");
		*fd = -1;
	}
}

void	protected_dup2(t_pipex *param, int oldfd, int newfd)
{
	if (oldfd != -1 && newfd != -1)
	{
		if (dup2(oldfd, newfd) == -1)
			perror_exit(param, "dup2", EXIT_FAILURE);
	}
}
