/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:08:10 by cwon              #+#    #+#             */
/*   Updated: 2025/01/13 15:31:31 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	validate_args(int argc, char **argv)
{
	char	*str1;
	char	*str2;

	str1 = "Usage:\t./pipex file1 cmd1 cmd2 <cmd3> ... <cmdn> file2\n";
	str2 = "\t./pipex here_doc LIMITER cmd cmd1 <cmd2> ... <cmdn> file\n";
	if (argc < 5 || (!ft_strncmp(argv[1], "here_doc", 9) && argc < 6))
	{
		ft_putstr_fd(str1, 2);
		ft_putstr_fd(str2, 2);
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	validate_args(argc, argv);
	pipex(argc, argv, envp);
	return (0);
}
