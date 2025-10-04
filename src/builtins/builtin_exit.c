/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregnaut <mregnaut@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:35:47 by mregnaut          #+#    #+#             */
/*   Updated: 2025/09/15 17:04:16 by mregnaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include <unistd.h>

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

int	builtin_exit(char **args, t_cmd *cmds_head)
{
	int	exit_code;

	if (!args[1])
	{
		if (isatty(STDIN_FILENO))
			printf("exit\n");
		free_commands(cmds_head);
		exit(0);
	}
	if (!is_number(args[1]))
	{
		if (isatty(STDIN_FILENO))
			printf("exit\n");
		fprintf(stderr, "minishell: exit: %s: numeric argument required\n",
			args[1]);
		free_commands(cmds_head);
		exit(2);
	}
	if (args[2])
	{
		if (isatty(STDIN_FILENO))
			printf("exit\n");
		fprintf(stderr, "minishell: exit: too many arguments\n");
		return (1);
	}
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	exit_code = ft_atoi(args[1]);
	free_commands(cmds_head);
	exit(exit_code);
}
