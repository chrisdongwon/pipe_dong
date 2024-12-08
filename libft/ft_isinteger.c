/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinteger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:17:48 by cwon              #+#    #+#             */
/*   Updated: 2024/11/21 18:26:04 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_overflow(const char *str, size_t length)
{
	char	*int_max;
	size_t	i;

	i = 0;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	if (length - i == 10)
	{
		int_max = "2147483647";
		while (i < length)
		{
			if (str[i] > int_max[i])
				return (1);
			i++;
		}
	}
	return (0);
}

static int	is_underflow(const char *str, size_t length)
{
	char	*int_min;
	size_t	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	if (length - i == 11)
	{
		int_min = "-2147483648";
		while (i < length)
		{
			if (str[i] > int_min[i])
				return (1);
			i++;
		}
	}
	return (0);
}

int	ft_isinteger(const char *str)
{
	size_t	i;
	size_t	length;

	length = ft_strlen(str);
	if (!length || ((length == 1) && !ft_isdigit(str[0])))
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (length - i > 10)
		return (0);
	while (i < length)
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	if (str[0] == '-' && is_underflow(str, length))
		return (0);
	if (is_overflow(str, length))
		return (0);
	return (1);
}
