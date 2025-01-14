/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:46:12 by cwon              #+#    #+#             */
/*   Updated: 2025/01/13 15:51:40 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_data(t_pipex *param, int argc, char **argv, char **envp)
{
	param->environ = envp;
	// param->env_paths = init_env_paths(env, param);
	param->here_doc = 0;
	param->limiter = 0;
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		param->here_doc = 1;
		param->limiter = argv[2];
	}
	param->file1 = argv[1]; // what if here_doc?
	param->file2 = argv[argc - 1];
	param->cmd_count = argc - 3 - param->here_doc;
	// param->commands = parse_cmd_list(argv + 2 + param->here_doc, param->n_cmd, param);
	param->last_status = 0;
}
