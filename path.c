/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 09:06:13 by cwon              #+#    #+#             */
/*   Updated: 2025/01/18 09:07:31 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*path_to_test(char *dir, char *cmd)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin(dir, "/");
	result = ft_strjoin(temp, cmd);
	free(temp);
	return (result);
}

static char	*match_path(char *cmd, char **paths)
{
	char	*result;
	size_t	i;

	if (!paths || (ft_strlen(cmd) > 1 && !ft_strncmp(cmd, "./", 2)))
		return (ft_strdup(cmd));
	i = 0;
	while (paths[i])
	{
		result = path_to_test(paths[i++], cmd);
		if (!access(result, F_OK))
			return (result);
		free(result);
	}
	return (ft_strdup(cmd));
}

static char	**get_paths(char **envp)
{
	char	**result;
	size_t	i;

	result = 0;
	i = 0;
	if (!envp[i])
		result = ft_split("/bin:/sbin:/usr/bin:/usr/sbin", ':');
	else
	{
		while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
			i++;
		if (envp[i])
			result = ft_split(envp[i], ':');
	}
	return (result);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*result;

	paths = get_paths(envp);
	result = match_path(cmd, paths);
	if (paths)
		flush_str_array(paths);
	return (result);
}
