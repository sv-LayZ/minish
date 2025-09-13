/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregnaut <mregnaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:08:47 by mregnaut          #+#    #+#             */
/*   Updated: 2024/11/11 20:04:36 by mregnaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	i;
	size_t	j;

	if (*n == '\0')
		return ((char *)h);
	i = 0;
	while (h[i] && i < len)
	{
		j = 0;
		while (h[i + j]
			&& n[j]
			&& i + j < len
			&& h[i + j] == n[j])
			j++;
		if (n[j] == '\0')
			return ((char *)(h + i));
		i++;
	}
	return (NULL);
}
