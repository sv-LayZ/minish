/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 00:00:00 by ai-helper         #+#    #+#             */
/*   Updated: 2025/10/02 01:09:41 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

int	consume_heredocs(t_redir *redirections)
{
	int	count;
	int	fd;

	count = 0;
	while (redirections)
	{
		if (redirections->type == TOKEN_HEREDOC)
		{
			fd = handle_heredoc(redirections->file, count,
					redirections->expand);
			if (fd == -1)
				return (1);
			close(fd);
			count++;
		}
		redirections = redirections->next;
	}
	return (0);
}
