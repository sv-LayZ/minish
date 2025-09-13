/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:35:47 by mregnaut          #+#    #+#             */
/*   Updated: 2025/08/05 23:52:57 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args)
{
	int	exit_code;

	printf("exit\n");
	if (!args[1])
		exit(0);
	if (!is_number(args[1]))
	{
		fprintf(stderr, "minishell: exit: %s: numeric argument required\n",
			args[1]);
		exit(2);
	}
	if (args[2])
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	exit(exit_code);
}
