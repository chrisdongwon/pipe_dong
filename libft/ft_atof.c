/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:12:57 by cwon              #+#    #+#             */
/*   Updated: 2024/12/03 21:47:38 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init_atof(double *result, double *sign, double *decimal_place)
{
	*result = 0;
	*sign = 1;
	*decimal_place = 1;
}

double	ft_atof(const char *nptr)
{
	double	result;
	double	sign;
	double	decimal_place;

	init_atof(&result, &sign, &decimal_place);
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
		result = result * 10 + (*(nptr++) - '0');
	if (*(nptr++) == '.')
	{
		while (ft_isdigit(*nptr))
		{
			decimal_place *= 10;
			result = result + (*(nptr++) - '0') / decimal_place;
		}
	}
	return (sign * result);
}
