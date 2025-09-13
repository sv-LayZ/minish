/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:35:47 by mregnaut          #+#    #+#             */
/*   Updated: 2025/07/31 21:42:18 by Hadia            ###   ########.fr       */
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

int	execute_builtin(int index, char **args)
{
	static int	(*builtin_func[])(char **) = {BUILTIN_FUNCS};

	if (index == -1)
		return (-1);
	return (builtin_func[index](args));
}
