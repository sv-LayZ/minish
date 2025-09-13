/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregnaut <mregnaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:33:20 by mregnaut          #+#    #+#             */
/*   Updated: 2024/11/09 15:51:09 by mregnaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = NULL;
	while (n--)
	{
		if (*(unsigned char *)s == (unsigned char)c)
		{
			ptr = (unsigned char *)s;
			break ;
		}
		s++;
	}
	return (ptr);
}
