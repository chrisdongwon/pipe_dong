/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 00:48:30 by cwon              #+#    #+#             */
/*   Updated: 2025/01/13 14:38:30 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	is_whitespace_command(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (!ft_isspace(str[i++]))
			return (0);
	}
	return (1);
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

void	finalize_token(t_tokenizer *data)
{
	if (data->i)
	{
		(data->buffer)[data->i] = 0;
		append_token(&(data->list), data->buffer);
		data->i = 0;
	}
}
