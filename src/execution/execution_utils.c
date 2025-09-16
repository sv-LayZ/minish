/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregnaut <mregnaut@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/15 19:57:35 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

static int apply_one_redir(t_redir *r)
{
	int fd;

	if (r->type == TOKEN_REDIRECT_IN)
	{
		fd = open(r->file, O_RDONLY);
		if (fd == -1)
		{
			perror(r->file);
			return (-1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			return (-1);
		}
		close(fd);
	}
	else if (r->type == TOKEN_REDIRECT_OUT || r->type == TOKEN_REDIRECT_APPEND)
	{
		int flags = O_WRONLY | O_CREAT;
		if (r->type == TOKEN_REDIRECT_APPEND)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd = open(r->file, flags, 0644);
		if (fd == -1)
		{
			perror(r->file);
			return (-1);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			return (-1);
		}
		close(fd);
	}
	else if (r->type == TOKEN_HEREDOC)
	{
		ft_putstr_fd("minishell: heredoc not implemented yet\n", 2);
		return (-1);
	}
	return (0);
}

int apply_redirections(t_redir *redirections)
{
	t_redir *r;

	r = redirections;
	while (r)
	{
		if (apply_one_redir(r) == -1)
			return (-1);
		r = r->next;
	}
	return (0);
}
