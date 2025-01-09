/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_bonus_util.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:39:11 by cwon              #+#    #+#             */
/*   Updated: 2025/01/09 12:39:25 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_tokenizer(t_list **node, t_tokenizer *data, char *input)
{
	*node = 0;
	data->str = input;
	data->len = ft_strlen(input);
	data->i = 0;
	data->j = 0;
	data->single_quote = 0;
	data->double_quote = 0;
}

void	append_token(t_list **head, char *token)
{
	t_list	*node;
	char	*data;

	data = ft_strdup(token);
	if (!data)
	{
		ft_lstclear(head, free);
		*head = 0;
		return ;
	}
	node = ft_lstnew(data);
	if (!node)
	{
		ft_lstclear(head, free);
		*head = 0;
		return ;
	}
	ft_lstadd_back(head, node);
}

char	**list_to_array(t_list *node)
{
	char	**result;
	size_t	i;

	result = (char **)malloc((ft_lstsize(node) + 1) * sizeof(char *));
	if (!result)
		return (0);
	i = 0;
	while (node)
	{
		result[i] = ft_strdup(node->content);
		if (!result[i])
		{
			flush_str_array(result);
			return (0);
		}
		node = node->next;
		i++;
	}
	result[i] = 0;
	return (result);
}

int	whitespace_command(char *str)
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
