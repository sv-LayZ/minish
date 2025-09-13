/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregnaut <mregnaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:00:28 by mregnaut          #+#    #+#             */
/*   Updated: 2024/11/11 19:20:26 by mregnaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen(str) + 1;
	ptr = NULL;
	while (len--)
	{
		if (*str == (char)c)
			ptr = (char *)str;
		str++;
	}
	return (ptr);
}
