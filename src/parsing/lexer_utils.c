/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:10:14 by dedme             #+#    #+#             */
/*   Updated: 2025/10/02 19:25:43 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

int	skip_whitespace(const char *line, int i)
{
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

int	get_operator_length(const char *line, int i)
{
	if (line[i] == '<' && line[i + 1] == '<')
		return (2);
	if (line[i] == '>' && line[i + 1] == '>')
		return (2);
	if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		return (1);
	return (0);
}

char	*extract_word(const char *line, int start, int end)
{
	char	*word;
	int		i;

	if (end < start)
		return (NULL);
	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = line[start++];
	word[i] = '\0';
	return (word);
}

void	add_word_token(const char *line, int s, int e,
		t_quote_type q, t_token **tokens)
{
	char	*value;

	if (e > s)
	{
		value = extract_word(line, s, e);
		if (value)
		{
			append_token(tokens, create_token(TOKEN_ARGUMENT, value, q));
			free(value);
		}
	}
}

t_quote_type	get_start_quote(const char *line, int *i)
{
	if (line[*i] == '\'')
		return ((*i)++, SINGLE_QUOTE);
	if (line[*i] == '"')
		return ((*i)++, DOUBLE_QUOTE);
	return (NO_QUOTE);
}
