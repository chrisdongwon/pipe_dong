/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:39:56 by cwon              #+#    #+#             */
/*   Updated: 2024/12/08 11:59:52 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <sys/types.h>

# include "libft/libft.h"

extern char	**environ;

// pipex.c
void	pipex(int argc, char *argv[]);

// parse_command.c
char	**parse_command(char *command);

// pipex_util.c
void	flush_str_array(char **array);
char	*get_pathname(char **argv);

#endif