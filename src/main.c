/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 23:00:58 by mregnaut          #+#    #+#             */
/*   Updated: 2025/10/01 18:20:21 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_status = 0;

static void	handle_only_heredoc(t_cmd *cmds)
{
	int		only_heredoc;
	t_redir	*r;

	only_heredoc = 1;
	r = cmds->redirections;
	while (r)
	{
		if (r->type != TOKEN_HEREDOC)
			only_heredoc = 0;
		r = r->next;
	}
	if (!only_heredoc)
		return ;
	if (consume_heredocs(cmds->redirections) == 0 && g_exit_status == 0)
		g_exit_status = 0;
	else if (g_exit_status != 130 && g_exit_status != 0)
		g_exit_status = 1;
}

static void	process_line(char *line)
{
	t_cmd	*cmds;

	cmds = parsing(line);
	if (DEBUGGING)
		debug_print_cmd(cmds);
	if (cmds)
	{
		if ((!cmds->args || !cmds->args[0]) && cmds->redirections)
			handle_only_heredoc(cmds);
		else if (cmds->args && cmds->args[0])
		{
			if (ft_strlen(cmds->args[0]) == 0)
			{
				ft_putstr_fd("minishell: : command not found\n", 2);
				g_exit_status = 127;
			}
			else
				g_exit_status = execute_pipeline(cmds);
		}
	}
	free_commands(cmds);
}

int	main(int ac, char **av)
{
	char	*line;

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
		process_line(line);
		free(line);
	}
	return (g_exit_status);
}
