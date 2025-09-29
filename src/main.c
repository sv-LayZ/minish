/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 23:00:58 by mregnaut          #+#    #+#             */
/*   Updated: 2025/09/29 20:05:49 by dedme            ###   ########.fr       */
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
		if (cmds)
		{
			/* Si la ligne ne contient que des heredocs (ex: <<e<<e) sans commande,
			 * on doit quand même les consommer comme bash --posix, puis ne rien exécuter. */
			if ((!cmds->args || !cmds->args[0]) && cmds->redirections)
			{
				int		only_heredoc = 1;
				t_redir	*r = cmds->redirections;
				while (r)
				{
					if (r->type != TOKEN_HEREDOC)
					{
						only_heredoc = 0;
						break;
					}
					r = r->next;
				}
				if (only_heredoc)
				{
					if (consume_heredocs(cmds->redirections) == 0 && g_exit_status == 0)
						g_exit_status = 0;
					else if (g_exit_status != 130 && g_exit_status != 0)
						g_exit_status = 1;
				}
			}
			else if (cmds->args && cmds->args[0])
			{
				/* Bash lit tous les heredocs d'une ligne avant de lancer la commande/pipeline. */
				{
					t_cmd *c = cmds;
					while (c)
					{
						consume_heredocs(c->redirections);
						c = c->next;
					}
				}
				if (g_exit_status == 0)
					g_exit_status = execute_pipeline(cmds);
			}
		}
		free_commands(cmds);
		free(line);
	}
	return (0);
}
