/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 08:53:12 by cwon              #+#    #+#             */
/*   Updated: 2024/12/30 21:49:53 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**tokenize(t_pipex *param, char *cmd)
{
	char	**result;

	result = protected_split(param, cmd, ' ');
	if (!result[0])
	{
		flush_str_array(result);
		return (whitespace_command(param, cmd));
	}
	return (result);
}
