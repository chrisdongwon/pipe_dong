/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:53:51 by cwon              #+#    #+#             */
/*   Updated: 2025/01/13 09:54:12 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumeric(const char *str)
{
	int		dot_count;
	size_t	i;
	size_t	str_len;

	dot_count = 0;
	i = 0;
	str_len = ft_strlen(str);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (i < str_len)
	{
		if (str[i] == '.')
		{
			dot_count++;
			if (dot_count > 1)
				return (0);
		}
		else if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
