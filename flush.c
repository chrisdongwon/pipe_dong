/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:08:54 by cwon              #+#    #+#             */
/*   Updated: 2025/01/13 10:19:20 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	flush_fd(t_pipex *param)
{
	protected_close(&(param->pipefd[0]));
	protected_close(&(param->pipefd[1]));
	protected_close(&(param->input_fd));
	protected_close(&(param->output_fd));
}

void	flush_pipex(t_pipex *param)
{
	flush_fd(param);
	free(param->path1);
	free(param->path2);
	flush_str_array(param->cmd1);
	flush_str_array(param->cmd2);
	flush_str_array(param->envp);
}
