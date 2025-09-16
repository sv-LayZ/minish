/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregnaut <mregnaut@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:11:00 by mregnaut          #+#    #+#             */
/*   Updated: 2025/09/15 21:34:11 by mregnaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_redirection_token(t_token_type type)
{
	return (type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_REDIRECT_IN
		|| type == TOKEN_REDIRECT_APPEND
		|| type == TOKEN_HEREDOC);
}
