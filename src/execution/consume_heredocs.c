/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 00:00:00 by ai-helper         #+#    #+#             */
/*   Updated: 2025/09/29 20:05:49 by dedme            ###   ########.fr       */
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
	char	*tmp_name;

	count = 0;
	while (redirections)
	{
		if (redirections->type == TOKEN_HEREDOC)
		{
			close_sig();
			fd = handle_heredoc(redirections->file, count);
			handle_signals();
			if (fd == -1)
				return (1);
			/* Build temp name and keep path so execution phase can reopen last one */
			tmp_name = ft_strjoin("/tmp/heredoc_", ft_itoa(count));
			if (!tmp_name)
			{
				close(fd);
				return (1);
			}
			/* We already have fd opened READONLY by handle_heredoc (reopened inside). */
			redirections->heredoc_path = tmp_name;
			redirections->heredoc_done = 1;
			close(fd);
			count++;
		}
		redirections = redirections->next;
	}
	return (0);
}
