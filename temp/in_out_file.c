/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:38:51 by ugerkens          #+#    #+#             */
/*   Updated: 2025/01/19 17:44:25 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup_input(char *filename, char *limiter, t_data *d)
{
	int	input_fd;

	if (limiter != NULL)
		return ;
	else
	{
		input_fd = open(filename, O_RDONLY);
		if (input_fd == -1)
		{
			report_errno(filename, d);
			input_fd = s_open("/dev/null", O_RDONLY, 0, d);
		}
	}
	s_dup2(input_fd, STDIN_FILENO, d);
	s_close(input_fd, d);
}

void	setup_output(char *filename, t_data *d)
{
	int	output_fd;

	output_fd = s_open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644, d);
	s_dup2(output_fd, STDOUT_FILENO, d);
	s_close(output_fd, d);
}

