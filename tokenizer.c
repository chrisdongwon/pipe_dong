/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 23:04:27 by cwon              #+#    #+#             */
/*   Updated: 2025/01/13 14:40:13 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void	init_tokenizer(t_tokenizer *result)
{
	result->list = 0;
	result->buffer_size = 128;
	result->buffer = (char *)malloc(result->buffer_size);
	result->single_quote = 0;
	result->double_quote = 0;
	result->i = 0;
}

static void	flush_tokenizer(t_tokenizer *data)
{
	if (data->buffer)
	{
		free(data->buffer);
		data->buffer = 0;
	}
	if (data->list)
	{
		ft_lstclear(&(data->list), free);
		data->list = 0;
	}
}

static void	parse(t_tokenizer *data, char *ptr)
{
	while (*ptr)
	{
		data->c = *ptr;
		if (!data->single_quote && !data->double_quote && ft_isspace(data->c))
		{
			finalize_token(data);
			if (!data->list)
				return ;
		}
		else if (data->c == '\'' && !data->double_quote)
			data->single_quote = !data->single_quote;
		else if (data->c == '\"' && !data->single_quote)
			data->double_quote = !data->double_quote;
		else
		{
			data->c = process_char(&ptr, data->single_quote);
			add_to_buffer(data, data->c);
			if (!data->buffer)
				return ;
		}
		ptr++;
	}
	finalize_token(data);
}

static char	**single_command(char *cmd)
{
	char	**result;

	result = (char **)malloc(2 * sizeof(char *));
	if (!result)
		return (0);
	result[0] = ft_strdup(cmd);
	result[1] = 0;
	if (!result[0])
	{
		free(result);
		return (0);
	}
	return (result);
}

char	**tokenize(char *cmd)
{
	char		**result;
	t_tokenizer	data;

	if (is_whitespace_command(cmd))
		return (single_command(cmd));
	init_tokenizer(&data);
	if (!data.buffer)
		return (0);
	parse(&data, cmd);
	if (!data.buffer || !data.list || data.single_quote || data.double_quote)
	{
		flush_tokenizer(&data);
		return (0);
	}
	result = list_to_str_array(data.list);
	flush_tokenizer(&data);
	return (result);
}
