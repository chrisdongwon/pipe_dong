/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:22:22 by cwon              #+#    #+#             */
/*   Updated: 2025/01/17 15:43:06 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	deallocate_append(t_pipex *param, char **args)
{
	t_list	*node;
	size_t	i;

	i = 0;
	while (args[i])
	{
		node = ft_lstnew(args[i++]);
		if (!node)
		{
			flush_str_array(args);
			error_exit(param, "lstnew", EXIT_FAILURE);
		}
		ft_lstadd_back(&(param->deallocate), node);
	}
	node = ft_lstnew(args);
	if (!node)
	{
		flush_str_array(args);
		error_exit(param, "lstnew", EXIT_FAILURE);
	}
	ft_lstadd_back(&(param->deallocate), node);
}

void	error_exit(t_pipex *param, char *s, int status)
{
	if (s)
	{
		ft_putstr_fd(s, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	flush_pipex(param);
	exit(status);
}

void	flush_pipex(t_pipex *param)
{
	safe_close(&(param->prev_fd));
	safe_close(&(param->file1_fd));
	safe_close(&(param->file2_fd));
	safe_close(&(param->pipefd[0]));
	safe_close(&(param->pipefd[1]));
	free(param->commands);
	ft_lstclear(&(param->deallocate), free);
}

void	perror_exit(t_pipex *param, char *s, int status)
{
	perror(s);
	flush_pipex(param);
	exit(status);
}

void	safe_close(int *fd)
{
	if (*fd != -1 && !close(*fd))
		*fd = -1;
}
