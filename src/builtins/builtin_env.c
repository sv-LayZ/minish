/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:35:47 by mregnaut          #+#    #+#             */
/*   Updated: 2025/08/22 15:22:51 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

extern char	**environ;

int	builtin_env(char **args)
{
	int	i;

	(void)args;
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "COLUMNS=", 8) == 0
			|| ft_strncmp(environ[i], "LINES=", 6) == 0)
		{
			i++;
			continue;
		}
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}
