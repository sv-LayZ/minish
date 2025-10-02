/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:06:00 by mregnaut          #+#    #+#             */
/*   Updated: 2025/10/02 19:25:53 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

/* Extract a word without surrounding quotes. */

static void	handle_operator(const char *line, int *i, t_token **tokens)
{
	int		op_len;
	char	*value;

	op_len = get_operator_length(line, *i);
	if (op_len > 0)
	{
		value = extract_word(line, *i, *i + op_len);
		if (value)
		{
			append_token(tokens, create_token(get_token_type(value), value,
					NO_QUOTE));
			free(value);
		}
		*i += op_len;
	}
}

static int	scan_word(const char *line, int *i, t_quote_type q)
{
	int	start;

	start = *i;
	while (line[*i] && ((q == NO_QUOTE && !ft_isspace(line[*i])
				&& !get_operator_length(line, *i))
			|| (q == SINGLE_QUOTE && line[*i] != '\'')
			|| (q == DOUBLE_QUOTE && line[*i] != '"')))
		(*i)++;
	if (q != NO_QUOTE && (line[*i] == '\'' || line[*i] == '"'))
		(*i)++;
	return (start);
}

static void	handle_word_or_quote(const char *line, int *i, t_token **tokens)
{
	int				start;
	int				end;
	t_quote_type	start_quote;

	start_quote = get_start_quote(line, i);
	start = scan_word(line, i, start_quote);
	end = *i;
	add_word_token(line, start, end, start_quote, tokens);
}

static t_token	*tokenize_line(const char *line)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		i = skip_whitespace(line, i);
		if (!line[i])
			break ;
		if (get_operator_length(line, i) > 0)
			handle_operator(line, &i, &tokens);
		else
			handle_word_or_quote(line, &i, &tokens);
	}
	return (tokens);
}

t_token	*lexer(const char *line)
{
	if (!line || !*line)
		return (NULL);
	return (tokenize_line(line));
}
