/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:10:00 by mregnaut          #+#    #+#             */
/*   Updated: 2025/09/29 20:05:49 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

t_redir	*create_redirection(t_token_type type, char *file)
{
	t_redir	*redir;

	if (!file)
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = file;
	redir->heredoc_path = NULL;
	redir->heredoc_done = 0;
	redir->next = NULL;
	return (redir);
}

void	append_redirection(t_redir **head, t_redir *new_redir)
{
	t_redir	*current;

	if (!head || !new_redir)
		return ;
	if (!*head)
	{
		*head = new_redir;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

void	free_redirections(t_redir *head)
{
	t_redir	*current;
	t_redir	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->file);
		if (current->heredoc_path)
			free(current->heredoc_path);
		free(current);
		current = next;
	}
}
