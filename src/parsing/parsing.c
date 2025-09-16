/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregnaut <mregnaut@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:05:00 by mregnaut          #+#    #+#             */
/*   Updated: 2025/09/15 21:33:25 by mregnaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

t_cmd	*parsing(char *line)
{
	t_token	*tokens;
	t_cmd	*commands;

	if (!line || !*line)
		return (NULL);
	tokens = lexer(line);
	if (!tokens)
		return (NULL);
	commands = parser(tokens);
	free_tokens(tokens);
	return (commands);
}
