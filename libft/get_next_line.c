/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregnaut <mregnaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:47:14 by mregnaut          #+#    #+#             */
/*   Updated: 2025/04/15 16:49:35 by mregnaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_writetobuf(ssize_t *nb_read, char *buf, int fd)
{
	*nb_read = read(fd, buf, BUFFER_SIZE);
	buf[*nb_read] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		eol;
	ssize_t		nb_read;

	line = NULL;
	eol = -1;
	nb_read = 1;
	while (nb_read != 0 && eol == -1)
	{
		if (!buf[0])
			ft_writetobuf(&nb_read, buf, fd);
		if (nb_read == -1)
			return (ft_free(line));
		if (nb_read != 0)
		{
			eol = ft_eolgap(buf);
			line = ft_add_buf_to_line(line, buf, eol);
			if (!line)
				return (NULL);
			ft_pending_buf(buf, eol);
		}
	}
	return (line);
}
