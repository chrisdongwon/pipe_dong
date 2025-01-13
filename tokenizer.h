/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 23:01:01 by cwon              #+#    #+#             */
/*   Updated: 2025/01/13 10:43:51 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "libft/libft.h"

typedef struct s_tokenizer
{
	char	*buffer;
	char	c;
	int		double_quote;
	int		single_quote;
	size_t	i;
	size_t	buffer_size;
	t_list	*list;
}	t_tokenizer;

// tokenizer.c
char	**tokenize(char *cmd);

// tokenizer_util.c
int		is_whitespace_command(char *str);
char	process_char(char **ptr, int single_quote);
void	add_to_buffer(t_tokenizer *data, char c);
void	finalize_token(t_tokenizer *data);

// list_util.c
char	**list_to_str_array(t_list *node);
void	add_to_buffer(t_tokenizer *data, char c);
void	append_token(t_list **list, char *token);
void	flush_str_array(char **arr);

#endif