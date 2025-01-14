/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinteger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:17:48 by cwon              #+#    #+#             */
/*   Updated: 2025/01/14 09:49:40 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_overflow(const char *nptr, size_t length)
{
	char	*int_max;
	size_t	i;

	i = 0;
	if (nptr[i] == '-')
		return (0);
	if (nptr[i] == '+')
		i++;
	if (length - i == 10)
	{
		int_max = "2147483647";
		while (i < length)
		{
			if (nptr[i] > int_max[i])
				return (1);
			i++;
		}
	}
	return (0);
}

static int	is_underflow(const char *nptr, size_t length)
{
	char	*int_min;
	size_t	i;

	i = 0;
	if (nptr[i] != '-')
		return (0);
	if (length - i == 11)
	{
		int_min = "-2147483648";
		while (i < length)
		{
			if (nptr[i] > int_min[i])
				return (1);
			i++;
		}
	}
	return (0);
}

int	ft_isinteger(const char *nptr)
{
	size_t	i;
	size_t	length;

	length = ft_strlen(nptr);
	if (!length || ((length == 1) && !ft_isdigit(nptr[0])))
		return (0);
	i = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	if (length - i > 10)
		return (0);
	while (i < length)
	{
		if (!ft_isdigit(nptr[i++]))
			return (0);
	}
	if (nptr[0] == '-' && is_underflow(nptr, length))
		return (0);
	if (is_overflow(nptr, length))
		return (0);
	return (1);
}
