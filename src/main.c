/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregnaut <mregnaut@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 23:00:58 by mregnaut          #+#    #+#             */
/*   Updated: 2025/09/16 03:21:47 by mregnaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_status = 0;

int	main(int ac, char **av)
{
	char	*line;
	t_cmd	*cmds;

	(void)ac;
	(void)av;
	handle_signals();
	while (1)
	{
		line = reader();
		if (!line)
			continue ;
		if (ft_strlen(line) > 0)
			add_history(line);
		cmds = parsing(line);
		if (DEBUGGING)
			debug_print_cmd(cmds);
		if (cmds && cmds->args && cmds->args[0])
			g_exit_status = execute_pipeline(cmds);
		free_commands(cmds);
		free(line);
	}
	return (0);
}
