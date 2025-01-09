/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:37:08 by cwon              #+#    #+#             */
/*   Updated: 2025/01/09 12:37:28 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	parse_single(char c, char *buffer, t_tokenizer *data)
{
	if (c == '\'')
		data->single_quote = 0;
	else
		buffer[data->j++] = c;
}

static void	parse_double(char c, char *buffer, t_tokenizer *data)
{
	if (c == '"')
		data->double_quote = 0;
	else if (c == '\\')
	{
		if (++data->i < data->len)
		{
			c = data->str[data->i];
			buffer[data->j++] = c;
		}
	}
	else
		buffer[data->j++] = c;
}

static void	parse_token(char c, char *buffer, t_tokenizer *data, t_list **node)
{
	if (ft_isspace(c))
	{
		if (data->j)
		{
			buffer[data->j] = 0;
			append_token(node, buffer);
			data->j = 0;
		}
	}
	else if (c == '\'')
		data->single_quote = 1;
	else if (c == '"')
		data->double_quote = 1;
	else if (c == '\\')
	{
		if (++data->i < data->len)
		{
			c = data->str[data->i];
			buffer[data->j++] = c;
		}
	}
	else
		buffer[data->j++] = c;
}

static t_list	*parse(char *input)
{
	t_list		*node;
	char		c;
	char		buffer[1024];
	t_tokenizer	data;

	init_tokenizer(&node, &data, input);
	while (data.i < data.len)
	{
		c = input[data.i];
		if (data.single_quote)
			parse_single(c, buffer, &data);
		else if (data.double_quote)
			parse_double(c, buffer, &data);
		else
			parse_token(c, buffer, &data, &node);
		data.i++;
	}
	if (data.j)
	{
		buffer[data.j] = 0;
		append_token(&node, buffer);
	}
	return (node);
}

char	**tokenize(t_pipex *param, char *cmd)
{
	char	**result;
	t_list	*node;

	if (whitespace_command(cmd))
	{
		result = (char **)malloc(2 * sizeof(char *));
		if (!result)
			error_exit(param, "tokenize() failed", 1);
		result[0] = protected_strdup(param, cmd);
		result[1] = 0;
		return (result);
	}
	node = parse(cmd);
	if (!node)
		error_exit(param, "tokenize() failed", 1);
	result = list_to_array(node);
	ft_lstclear(&node, free);
	if (!result)
		error_exit(param, "tokenize() failed", 1);
	return (result);
}
