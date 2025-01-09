/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:23:04 by cwon              #+#    #+#             */
/*   Updated: 2025/01/09 13:36:11 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	*flush_str_array(char **arr)
{
	size_t	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
	return (0);
}

static void	flush_fd(t_pipex *param)
{
	protected_close(&(param->pipefd[0]));
	protected_close(&(param->pipefd[1]));
	protected_close(&(param->input_fd));
	protected_close(&(param->output_fd));
}

static void	flush_cmd_array(t_pipex *param)
{
	ssize_t	i;

	if (!param->arg_array)
		return ;
	i = 0;
	while (i < param->arg_count)
	{
		free(param->arg_array[i].path);
		flush_str_array(param->arg_array[i].cmd);
		i++;
	}
	free(param->arg_array);
}

void	flush_pipex(t_pipex *param)
{
	flush_fd(param);
	flush_str_array(param->envp);
	flush_cmd_array(param);
}
