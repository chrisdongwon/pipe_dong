/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:38:17 by ugerkens          #+#    #+#             */
/*   Updated: 2025/01/19 17:42:17 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*s_alloc(void *pointer, t_alloc mode, t_data *d)
{
	if (!pointer)
		error("Memory allocation", strerror(errno), EXIT_FAILURE, d);
	if (mode == TRACK)
		track_alloc(d, pointer);
	return (pointer);
}

void	track_alloc(t_data *d, void *pointer)
{
	t_list	*new_node;

	new_node = ft_lstnew(pointer);
	if (!new_node)
	{
		free(pointer);
		error("Memory allocation", strerror(errno), EXIT_FAILURE, d);
	}
	ft_lstadd_front(&d->allocated_pointers, new_node);
}
