/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:33:43 by cwon              #+#    #+#             */
/*   Updated: 2024/12/30 17:59:33 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**protected_split(t_pipex *param, char *str, char c)
{
	char	**result;

	result = ft_split(str, c);
	if (!result)
		error_exit(param, "split() failed", EXIT_FAILURE);
	return (result);
}

char	*protected_strjoin(t_pipex *param, char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (!result)
		error_exit(param, "strjoin() failed", EXIT_FAILURE);
	return (result);
}

char	*protected_strdup(t_pipex *param, char *str)
{
	char	*result;

	result = ft_strdup(str);
	if (!result)
		error_exit(param, "strdup() failed", EXIT_FAILURE);
	return (result);
}

char	*protected_substr(t_pipex *param, char *str, size_t start, size_t len)
{
	char	*result;

	result = ft_substr(str, start, len);
	if (!result)
		error_exit(param, "substr() failed", EXIT_FAILURE);
	return (result);
}
