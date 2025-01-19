/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:48:13 by cwon              #+#    #+#             */
/*   Updated: 2025/01/19 17:29:40 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**safe_split(t_pipex *param, char *str, char c)
{
	char	**result;

	result = ft_split(str, c);
	if (!result)
		flush_exit(param, "split", EXIT_FAILURE);
	deallocate_append_str_array(param, result);
	return (result);
}

static char	*potential_path(t_pipex *param, char *dir, char *cmd)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin(dir, "/");
	result = ft_strjoin(temp, cmd);
	free(temp);
	if (!result)
		flush_exit(param, "strjoin", EXIT_FAILURE);
	return (result);
}

static char	*get_path(t_pipex *param, char *cmd, char **envp)
{
	char	*result;
	size_t	i;

	if (!envp || (ft_strlen(cmd) > 1 && !ft_strncmp(cmd, "./", 2)))
		return (ft_strdup(cmd));
	i = 0;
	while (envp[i])
	{
		result = potential_path(param, envp[i++], cmd);
		if (!access(result, F_OK))
			return (result);
		free(result);
	}
	return (ft_strdup(cmd));
}

char	**init_env_path(t_pipex *param)
{
	char	**envp;
	size_t	i;

	envp = 0;
	i = 0;
	if (!param->environ[i])
		envp = safe_split(param, "/bin:/sbin:/usr/bin:/usr/sbin", ':');
	else
	{
		while (param->environ[i] && ft_strncmp(param->environ[i], "PATH=", 5))
			i++;
		if (param->environ[i])
			envp = safe_split(param, param->environ[i], ':');
	}
	return (envp);
}

char	*find_command_path(t_pipex *param, char *cmd)
{
	char	*result;

	result = get_path(param, cmd, param->env_path);
	if (!result)
		flush_exit(param, "get_path", EXIT_FAILURE);
	deallocate_append(param, result);
	return (result);
}
