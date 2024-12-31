/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:46:53 by cwon              #+#    #+#             */
/*   Updated: 2024/12/30 18:40:39 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*potential_path(t_pipex *param, char *dir, char *cmd)
{
	char	*result;
	char	*temp;

	temp = protected_strjoin(param, dir, "/");
	result = ft_strjoin(temp, cmd);
	free(temp);
	if (!result)
		error_exit(param, "strjoin() failed", EXIT_FAILURE);
	return (result);
}
