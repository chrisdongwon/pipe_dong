/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_flush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:18:58 by cwon              #+#    #+#             */
/*   Updated: 2025/01/18 12:41:49 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	deallocate_append_str_array(t_pipex *param, char **arr)
{
	t_list	*node;
	size_t	i;

	i = 0;
	while (arr[i])
	{
		node = ft_lstnew(arr[i++]);
		if (!node)
		{
			flush_str_array(arr);
			flush_exit(param, "lstnew", EXIT_FAILURE);
		}
		ft_lstadd_back(&(param->deallocate), node);
	}
	deallocate_append(param, arr);
}

void	deallocate_append(t_pipex *param, void *ptr)
{
	t_list	*node;

	node = ft_lstnew(ptr);
	if (!node)
	{
		free(ptr);
		flush_exit(param, "lstnew", EXIT_FAILURE);
	}
	ft_lstadd_back(&(param->deallocate), node);
}

void	flush_exit(t_pipex *param, char *error_message, int status)
{
	if (error_message)
	{
		ft_putstr_fd(error_message, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	flush_pipex(param);
	exit(status);
}

void	flush_pipex(t_pipex *param)
{
	close(param->file1_fd);
	close(param->file2_fd);
	free(param->commands);
	ft_lstclear(&(param->deallocate), free);
}

void	perror_exit(t_pipex *param, char *s, int status)
{
	perror(s);
	flush_pipex(param);
	exit(status);
}
