/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:15:09 by cwon              #+#    #+#             */
/*   Updated: 2025/01/13 09:38:55 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	**list_to_str_array(t_list *node)
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

void	append_token(t_list **list, char *token)
{
	t_list	*node;
	char	*data;

	data = ft_strdup(token);
	if (!data)
	{
		ft_lstclear(list, free);
		*list = 0;
		return ;
	}
	node = ft_lstnew(data);
	if (!node)
	{
		ft_lstclear(list, free);
		*list = 0;
		return ;
	}
	ft_lstadd_back(list, node);
}

void	flush_str_array(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
