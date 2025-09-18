/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:06:00 by mregnaut          #+#    #+#             */
/*   Updated: 2025/09/18 23:51:44 by dedme            ###   ########.fr       */
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

static int	handle_quotes(const char *line, int i, t_quote_type *quote)
{
	printf("%c\n", line[i]);
	if (line[i] == '\'' && *quote == NO_QUOTE)
	{
		printf("open quote\n");
		*quote = SINGLE_QUOTE;
		return (i + 1);
	}
	else if (line[i] == '\'' && *quote == SINGLE_QUOTE)
	{
		printf("already open\n");
		return (i + 1);
	}
	else if (line[i] == '"' && *quote == NO_QUOTE)
	{
		printf("double quote open\n");
		*quote = DOUBLE_QUOTE;
		return (i + 1);
	}
	else if (line[i] == '"' && *quote == DOUBLE_QUOTE)
	{
		printf("double quote already\n");
		*quote = NO_QUOTE;
		return (i+1);
	}
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

static char	*extract_word(const char *line, int start, int end)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
	{
		if (line[start] != '\'' && line[start] != '"')
			word[i++] = line[start];
		start++;
	}
	word[i] = '\0';
	return (word);
}

static t_token	*tokenize_line(const char *line)
{
	t_token			*tokens;
	t_quote_type	quote;
	int				i;
	int				start;
	int				op_len;
	char			*value;

	tokens = NULL;
	quote = NO_QUOTE;
	i = 0;
	while (line[i])
	{
		i = skip_whitespace(line, i);
		if (!line[i])
			break ;
		if (quote == NO_QUOTE && (op_len = get_operator_length(line, i)) > 0)
		{
			value = extract_word(line, i, i + op_len);
			if (value)
			{
				append_token(&tokens,
					create_token(get_token_type(value), value, NO_QUOTE));
				free(value);
			}
			i += op_len;
			continue ;
		}
		start = i;
		i = handle_quotes(line, i, &quote);
		if (i != start)
			continue ;
		start = i;
		while (line[i] && (quote != NO_QUOTE
				|| (!ft_isspace(line[i]) && get_operator_length(line, i) == 0)))
		{
			i = handle_quotes(line, i, &quote);
			printf("line[%d] = %c\n", i, line[i]);
			if (line[i] && (quote != NO_QUOTE
					|| (!ft_isspace(line[i])
						&& get_operator_length(line, i) == 0)))
				i++;
		}
		if (i > start)
		{
			value = extract_word(line, start, i);
			if (value)
			{
				append_token(&tokens,
					create_token(TOKEN_ARGUMENT, value, quote));
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
