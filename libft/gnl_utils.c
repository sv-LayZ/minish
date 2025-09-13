/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregnaut <mregnaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:36:02 by csavreux          #+#    #+#             */
/*   Updated: 2025/04/15 16:50:42 by mregnaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free(char *str)
{
	free(str);
	return (NULL);
}

char	*ft_add_buf_to_line(char *line, char *buf, ssize_t end)
{
	char	*newline;
	size_t	size_line;
	ssize_t	i;

	i = -1;
	size_line = ft_strlen(line);
	if (end == -1)
		end = ft_strlen(buf) - 1;
	newline = malloc((size_line + end + 2) * sizeof(char));
	if (!newline)
	{
		buf[0] = '\0';
		return (ft_free(line));
	}
	while ((size_line != 0) && line[++i])
		newline[i] = line[i];
	i = -1;
	while (++i <= end)
		newline[size_line + i] = buf[i];
	newline[size_line + i] = '\0';
	free(line);
	return (newline);
}

void	ft_pending_buf(char *buf, ssize_t start)
{
	size_t	i;

	i = 0;
	while ((start != -1) && buf[start + 1])
	{
		buf[i] = buf[start + 1];
		i++;
		start++;
	}
	buf[i] = '\0';
}

ssize_t	ft_eolgap(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
	{
		if (str[len] == '\n')
			return (len);
		len++;
	}
	return (-1);
}
