/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:07:31 by cwon              #+#    #+#             */
/*   Updated: 2025/01/08 13:59:27 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(t_pipex *param, char *message, int exit_code)
{
	if (message)
	{
		ft_putstr_fd(message, 2);
		ft_putstr_fd("\n", 2);
	}
	flush_pipex(param);
	exit(exit_code);
}

void	perror_exit(t_pipex *param, char *message, int exit_code)
{
	perror(message);
	flush_pipex(param);
	exit(exit_code);
}
