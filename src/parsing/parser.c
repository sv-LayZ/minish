/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:07:00 by mregnaut          #+#    #+#             */
/*   Updated: 2025/10/16 10:53:04 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

static t_cmd	*parse_command(t_token **current)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = create_command();
	if (!cmd)
		return (NULL);
	token = *current;
	while (token && token->type != TOKEN_PIPE)
	{
		if (is_redirection_token(token->type))
		{
			if (!token->next)
			{
				free_commands(cmd);
				return (NULL);
			}
			// For heredoc, determine expansion based on the quote_type of the delimiter token
			if (token->type == TOKEN_HEREDOC)
			{
				int expand = (token->next->quote_type == NO_QUOTE);
				append_redirection(&cmd->redirections,
					create_redirection(token->type, ft_strdup(token->next->value), expand));
			}
			else
			{
				char *filename;

				// Expand variables in filename unless it's single-quoted
				if (token->next->quote_type == SINGLE_QUOTE)
					filename = ft_strdup(token->next->value);
				else
				{
					filename = expand_variables(token->next->value);
					if (!filename)
						filename = ft_strdup(token->next->value);
				}
				append_redirection(&cmd->redirections,
					create_redirection(token->type, filename, 0));
			}
			token = token->next->next;
		}
		else if (token->type == TOKEN_ARGUMENT || token->type == TOKEN_COMMAND)
		{
			char *arg_value;

			// Expand variables unless it's a single-quoted string
			if (token->quote_type == SINGLE_QUOTE)
				arg_value = ft_strdup(token->value);
			else
			{
				arg_value = expand_variables(token->value);
				if (!arg_value)
					arg_value = ft_strdup(token->value);
			}

			if (!cmd->name)
				cmd->name = ft_strdup(arg_value);
			add_argument(cmd, arg_value);
			free(arg_value);
			token = token->next;
		}
		else
			token = token->next;
	}
	*current = token;
	return (cmd);
}

static t_cmd	*parse_pipeline(t_token *tokens)
{
	t_cmd	*commands;
	t_cmd	*current_cmd;
	t_token	*current_token;

	commands = NULL;
	current_token = tokens;
	while (current_token)
	{
		current_cmd = parse_command(&current_token);
		if (!current_cmd)
		{
			free_commands(commands);
			return (NULL);
		}
		append_command(&commands, current_cmd);
		if (current_token && current_token->type == TOKEN_PIPE)
			current_token = current_token->next;
	}
	return (commands);
}

t_cmd	*parser(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	return (parse_pipeline(tokens));
}
