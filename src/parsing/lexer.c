/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:06:00 by mregnaut          #+#    #+#             */
/*   Updated: 2025/09/22 18:12:12 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

static int	skip_whitespace(const char *line, int i)
{
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

static int	get_operator_length(const char *line, int i)
{
	if (line[i] == '<' && line[i + 1] == '<')
		return (2);
	if (line[i] == '>' && line[i + 1] == '>')
		return (2);
	if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		return (1);
	return (0);
}

/* Extract a word without surrounding quotes. */
static char	*extract_word(const char *line, int start, int end)
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

static t_token	*tokenize_line(const char *line)
{
	t_token			*tokens;
	int				i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		int				op_len;

		i = skip_whitespace(line, i);
		if (!line[i])
			break ;
		if ((op_len = get_operator_length(line, i)) > 0)
		{
			char	*value = extract_word(line, i, i + op_len);

			if (value)
			{
				append_token(&tokens,
					create_token(get_token_type(value), value, NO_QUOTE));
				free(value);
			}
			i += op_len;
			continue ;
		}
		t_quote_type	start_quote = NO_QUOTE;
		int				start;

		if (line[i] == '\'')
		{
			start_quote = SINGLE_QUOTE;
			i++;
		}
		else if (line[i] == '"')
		{
			start_quote = DOUBLE_QUOTE;
			i++;
		}
		start = i;
		if (start_quote != NO_QUOTE)
			while (line[i] && !((start_quote == SINGLE_QUOTE && line[i] == '\'')
					|| (start_quote == DOUBLE_QUOTE && line[i] == '"')))
				i++;
		else
		{
			while (line[i] && !ft_isspace(line[i]) && get_operator_length(line, i) == 0)
				i++;
		}
		int	end = i;
		if (start_quote != NO_QUOTE && (line[i] == '\'' || line[i] == '"'))
			i++;
		if (end > start)
		{
			char	*value = extract_word(line, start, end);

			if (value)
			{
				append_token(&tokens, create_token(TOKEN_ARGUMENT, value, start_quote));
				free(value);
			}
		}
	}
	return (tokens);
}

t_token	*lexer(const char *line)
{
	if (!line || !*line)
		return (NULL);
	return (tokenize_line(line));
}
