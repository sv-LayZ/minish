/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregnaut <mregnaut@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:35:47 by mregnaut          #+#    #+#             */
/*   Updated: 2025/09/15 17:04:27 by mregnaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	is_builtin(char *cmd)
{
	static char	*builtin_str[] = {BUILTIN_CMDS};
	int			i;

	if (!cmd)
		return (-1);
	i = 0;
	while (builtin_str[i])
	{
		if (ft_strcmp(cmd, builtin_str[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	execute_builtin(int index, char **args, t_cmd *cmds_head)
{
	static int	(*builtin_func[])(char **) = {BUILTIN_FUNCS};

	if (index == -1)
		return (-1);
	if (index == 6)
		return (builtin_exit(args, cmds_head));
	return (builtin_func[index](args));
}
