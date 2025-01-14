/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:22:32 by cwon              #+#    #+#             */
/*   Updated: 2025/01/14 10:25:43 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *array, size_t current_size, size_t new_size)
{
	char	*result;

	if (!array || !new_size)
	{
		if (array)
			free(array);
		return (0);
	}
	if (current_size == new_size)
		return (array);
	result = (char *)malloc(new_size);
	if (!result)
		return (0);
	if (current_size < new_size)
		ft_memcpy(result, array, current_size);
	else
		ft_memcpy(result, array, new_size);
	free(array);
	return (result);
}
