/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:35:47 by mregnaut          #+#    #+#             */
/*   Updated: 2025/07/31 21:42:43 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	builtin_unset(char **args)
{
	int	i;
	int	ret;

	if (!args[1])
		return (0);
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (unsetenv(args[i]) != 0)
		{
			perror("unset");
			ret = 1;
		}
		i++;
	}
	return (ret);
}
