/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregnaut <mregnaut@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:08:00 by mregnaut          #+#    #+#             */
/*   Updated: 2025/09/15 21:32:39 by mregnaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

t_token_type	get_token_type(const char *value)
{
	if (!value)
		return (TOKEN_OTHER);
	if (ft_strcmp(value, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(value, ">") == 0)
		return (TOKEN_REDIRECT_OUT);
	if (ft_strcmp(value, "<") == 0)
		return (TOKEN_REDIRECT_IN);
	if (ft_strcmp(value, ">>") == 0)
		return (TOKEN_REDIRECT_APPEND);
	if (ft_strcmp(value, "<<") == 0)
		return (TOKEN_HEREDOC);
	return (TOKEN_ARGUMENT);
}

t_token	*create_token(t_token_type type, const char *value, t_quote_type quote)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->quote_type = quote;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	append_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!head || !new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
	new_token->prev = current;
}

void	free_tokens(t_token *head)
{
	t_token	*current;
	t_token	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}
