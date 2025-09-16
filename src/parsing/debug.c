/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregnaut <mregnaut@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:15:00 by mregnaut          #+#    #+#             */
/*   Updated: 2025/09/15 23:39:03 by mregnaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

static void	debug_print_redirections(t_redir *redir)
{
	t_redir	*current;
	char	*type_str;

	current = redir;
	while (current)
	{
		if (current->type == TOKEN_REDIRECT_OUT)
			type_str = ">";
		else if (current->type == TOKEN_REDIRECT_IN)
			type_str = "<";
		else if (current->type == TOKEN_REDIRECT_APPEND)
			type_str = ">>";
		else if (current->type == TOKEN_HEREDOC)
			type_str = "<<";
		else
			type_str = "?";
		printf("      Redirection: %s %s\n", type_str, current->file);
		current = current->next;
	}
}

static void	debug_print_single_cmd(t_cmd *cmd, int cmd_num)
{
	int	i;

	printf("  Command %d:\n", cmd_num);
	printf("    Name: %s\n", cmd->name);
	if (cmd->args)
	{
		printf("    Args: ");
		i = 0;
		while (cmd->args[i])
			printf("[%s] ", cmd->args[i++]);
		printf("\n");
	}
	else
		printf("    Args: (null)\n");
	if (cmd->redirections)
	{
		printf("    Redirections:\n");
		debug_print_redirections(cmd->redirections);
	}
	else
		printf("    Redirections: none\n");
}

void	debug_print_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	int		cmd_num;

	if (!cmd)
	{
		printf("DEBUG: Command structure is NULL\n");
		return ;
	}
	printf("\e[1;93m=== DEBUG: Command Structure ===\n");
	current = cmd;
	cmd_num = 1;
	while (current)
	{
		debug_print_single_cmd(current, cmd_num);
		current = current->next;
		cmd_num++;
		if (current)
			printf("    -> PIPE to next command\n");
	}
	printf("=== End DEBUG ===\e[0m\n\n");
}
