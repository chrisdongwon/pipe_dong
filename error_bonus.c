/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:23:52 by cwon              #+#    #+#             */
/*   Updated: 2025/01/09 12:57:11 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
