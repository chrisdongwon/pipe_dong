/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 00:48:30 by cwon              #+#    #+#             */
/*   Updated: 2025/01/13 10:02:51 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void	resize_buffer(t_tokenizer *data)
{
	if (data->i + 1 >= data->buffer_size)
	{
		data->buffer = \
		ft_realloc(data->buffer, data->buffer_size, data->buffer_size * 2);
		if (!data->buffer)
			return ;
		data->buffer_size *= 2;
	}
}

char	process_char(char **ptr, int single_quote)
{
	char	result;

	result = **ptr;
	if (result == '\\' && !single_quote)
	{
		(*ptr)++;
		if (**ptr)
			result = **ptr;
	}
	return (result);
}

void	add_to_buffer(t_tokenizer *data, char c)
{
	resize_buffer(data);
	if (!data->buffer)
		return ;
	(data->buffer)[data->i] = c;
	(data->i)++;
}

void	finalize_token(t_tokenizer *data)
{
	if (data->i)
	{
		(data->buffer)[data->i] = 0;
		append_token(&(data->list), data->buffer);
		data->i = 0;
	}
}
