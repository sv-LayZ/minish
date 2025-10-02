/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:00:00 by ai-helper         #+#    #+#             */
/*   Updated: 2025/10/02 19:40:42 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ensure_capacity(char **buf, size_t *cap, size_t needed)
{
	char	*newbuf;
	size_t	newcap;

	if (*cap >= needed)
		return (1);
	if (*cap)
		newcap = *cap;
	else
		newcap = 64;
	while (newcap < needed)
		newcap *= 2;
	newbuf = (char *)malloc(newcap);
	if (!newbuf)
		return (0);
	if (*buf)
	{
		if (needed < *cap)
			ft_memcpy(newbuf, *buf, needed);
		else
			ft_memcpy(newbuf, *buf, *cap);
		free(*buf);
	}
	*buf = newbuf;
	*cap = newcap;
	return (1);
}

static int	append_char(char **buf, size_t *len, size_t *cap, char c)
{
	if (!ensure_capacity(buf, cap, *len + 2))
		return (0);
	(*buf)[(*len)++] = c;
	(*buf)[*len] = '\0';
	return (1);
}

static int	append_str(char **buf, size_t *len, size_t *cap, const char *s)
{
	size_t	slen;

	if (!s)
		return (1);
	slen = ft_strlen(s);
	if (!ensure_capacity(buf, cap, *len + slen + 1))
		return (0);
	ft_memcpy((*buf) + *len, s, slen);
	*len += slen;
	(*buf)[*len] = '\0';
	return (1);
}

char	*expand_exit_status(char **result, size_t *j, size_t *result_size)
{
	char	*status_str;
	char	*buf;
	size_t	cap;

	buf = *result;
	cap = *result_size;
	status_str = ft_itoa(g_exit_status);
	if (!status_str)
		return (NULL);
	if (!append_str(&buf, j, &cap, status_str))
	{
		free(status_str);
		return (NULL);
	}
	free(status_str);
	*result = buf;
	*result_size = cap;
	return (*result);
}

static int	append_env_value(char **result, size_t *j, size_t *cap, const char *name, size_t nlen)
{
	char	*key;
	char	*val;
	char	*buf;

	buf = *result;
	key = (char *)malloc(nlen + 1);
	if (!key)
		return (0);
	ft_memcpy(key, name, nlen);
	key[nlen] = '\0';
	val = getenv(key);
	free(key);
	if (!val)
		val = "";
	return (append_str(&buf, j, cap, val));
}

int	handle_dollar_sign(const char *line, size_t *i, t_expand_data *data)
{
	size_t	start;

	// line[*i] == '$' when called
	(*i)++;
	if (line[*i] == '?')
	{
		// Expand exit status
		(*i)++;
		if (!expand_exit_status(data->result, data->j, data->result_size))
			return (0);
		return (1);
	}
	// If invalid start for var name, keep '$' literally
	if (!line[*i] || (!ft_isalpha(line[*i]) && line[*i] != '_'))
		return (append_char(data->result, data->j, data->result_size, '$'));
	start = *i;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	if (!append_env_value(data->result, data->j, data->result_size, line + start, *i - start))
		return (0);
	return (1);
}

char	*expand_variables(const char *line)
{
	char		*result;
	size_t		len;
	size_t		cap;
	t_expand_data	data;
	size_t		i;

	result = NULL;
	len = 0;
	cap = 0;
	i = 0;
	if (!ensure_capacity(&result, &cap, 1))
		return (NULL);
	result[0] = '\0';
	data.result = &result;
	data.j = &len;
	data.result_size = &cap;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (!handle_dollar_sign(line, &i, &data))
			{
				free(result);
				return (NULL);
			}
			continue;
		}
		if (!append_char(&result, &len, &cap, line[i]))
		{
			free(result);
			return (NULL);
		}
		i++;
	}
	return (result);
}
