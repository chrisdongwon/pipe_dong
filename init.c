/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:00:49 by cwon              #+#    #+#             */
/*   Updated: 2025/01/01 14:38:15 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_param(t_pipex *param)
{
	param->cmd1 = 0;
	param->cmd2 = 0;
	param->envp = 0;
	param->path1 = 0;
	param->path2 = 0;
}

static void	init_envp(t_pipex *param)
{
	size_t	i;

	i = 0;
	if (!environ[i])
		param->envp = protected_split(param, "/bin:/sbin:/usr/bin:/usr/sbin", \
		':');
	else
	{
		while (environ[i] && ft_strncmp(environ[i], "PATH=", 5))
			i++;
		if (!environ[i])
			param->envp = 0;
		else
			param->envp = protected_split(param, environ[i], ':');
	}
}

static char	*init_path(t_pipex *param, char *cmd)
{
	char	*result;
	size_t	i;

	if (!param->envp || (ft_strlen(cmd) > 1 && !ft_strncmp(cmd, "./", 2)))
		return (protected_strdup(param, cmd));
	i = 0;
	while (param->envp[i])
	{
		result = potential_path(param, param->envp[i++], cmd);
		if (!access(result, F_OK))
			return (result);
		free(result);
	}
	return (protected_strdup(param, cmd));
}

static void	init_fd(t_pipex *param, char **argv)
{
	param->input_file = argv[1];
	param->output_file = argv[4];
	param->input_fd = protected_open(argv[1], O_RDONLY);
	param->output_fd = protected_open(argv[4], O_WRONLY | O_TRUNC | O_CREAT);
}

void	init_pipex(t_pipex *param, int argc, char **argv)
{
	if (argc != 5)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 2);
		exit(1);
	}
	init_param(param);
	param->cmd1 = tokenize(param, argv[2]);
	param->cmd2 = tokenize(param, argv[3]);
	init_envp(param);
	param->path1 = init_path(param, param->cmd1[0]);
	param->path2 = init_path(param, param->cmd2[0]);
	init_fd(param, argv);
	protected_pipe(param);
}
