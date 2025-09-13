/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregnaut <mregnaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:26:15 by mregnaut          #+#    #+#             */
/*   Updated: 2024/11/18 17:37:14 by mregnaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <limits.h>

int	ft_atoi(const char *nptr)
{
	long	r;
	char	n;

	n = 1;
	r = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
	{
		nptr++;
		n = -1;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		if (r -(*nptr - '0') > LONG_MAX / 10)
		{
			if (n == 1)
				return (-1);
			return (0);
		}
		r = r * 10 + (*nptr++ - '0');
	}
	return (r * n);
}
