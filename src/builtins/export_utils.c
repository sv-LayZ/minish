/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:58:00 by dedme             #+#    #+#             */
/*   Updated: 2025/10/02 01:05:14 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_identifier(char *arg)
{
	int	i;

	if (!arg || !*arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	set_env_var(char *arg)
{
	char	*equal_pos;

	if (!is_valid_identifier(arg))
		return (print_export_error(arg));
	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
		return (set_var_without_value(arg));
	return (set_var_with_value(arg, equal_pos));
}