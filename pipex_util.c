/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 18:07:43 by cwon              #+#    #+#             */
/*   Updated: 2024/12/07 23:40:56 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	flush_str_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

static void	flush_pipex(char **argv, char **paths)
{
	if (argv)
		flush_str_array(argv);
	if (paths)
		flush_str_array(paths);
	exit(EXIT_FAILURE);
}

static char	**get_paths(char **argv)
{
	char	**result;
	size_t	i;

	i = 0;
	while (environ[i] && ft_strncmp("PATH=", environ[i], 5))
		i++;
	if (!environ[i])
		flush_pipex(argv, 0);
	result = ft_split(environ[i] + 5, ':');
	if (!result)
		flush_pipex(argv, 0);
	return (result);
}

static char	*potential_path(char **paths, ssize_t i, char **argv)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin(paths[i], "/");
	if (!temp)
		return (0);
	result = ft_strjoin(temp, argv[0]);
	free(temp);
	if (!result)
		flush_pipex(argv, paths);
	return (result);
}

char	*get_pathname(char **argv)
{
	char	*result;
	char	**paths;
	ssize_t	i;

	paths = get_paths(argv);
	i = -1;
	while (paths[++i])
	{
		result = potential_path(paths, i, argv);
		if (!access(result, F_OK | X_OK))
		{
			flush_str_array(paths);
			return (result);
		}
		free(result);
	}
	flush_str_array(paths);
	return (ft_strdup(argv[0]));
}
