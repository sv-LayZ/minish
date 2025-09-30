/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 00:00:00 by ai-helper         #+#    #+#             */
/*   Updated: 2025/10/01 01:16:57 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

/*
 * Pre-consume heredocs exactly like bash does when parsing a simple command line
 * containing only redirections (e.g. <<e<<e<<e). Bash --posix reads all heredocs
 * even if there is no actual command following them. If the user enters only
 * heredocs, POSIX shells still collect the data and then effectively do nothing
 * with it (exit status 0 unless interrupted). We mimic that by opening each heredoc
 * and discarding the resulting fd. If an interruption (Ctrl-C) happens, we stop
 * early and return non-zero so the caller can skip further execution.
 */
int	consume_heredocs(t_redir *redirections)
{
	int		count;
	int		fd;

	count = 0;
	while (redirections)
	{
		if (redirections->type == TOKEN_HEREDOC)
		{
			fd = handle_heredoc(redirections->file, count, redirections->expand);
			if (fd == -1)
				return (1);
			close(fd);
			count++;
		}
		redirections = redirections->next;
	}
	return (0);
}
