/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregnaut <mregnaut@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:09:00 by mregnaut          #+#    #+#             */
/*   Updated: 2025/09/15 23:06:51 by mregnaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

t_cmd	*create_command(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	add_argument(t_cmd *cmd, char *arg)
{
	char	**new_args;
	int		argc;
	int		i;

	if (!cmd || !arg)
		return (0);
	argc = 0;
	if (cmd->args)
		while (cmd->args[argc])
			argc++;
	new_args = malloc(sizeof(char *) * (argc + 2));
	if (!new_args)
		return (0);
	i = 0;
	if (cmd->args)
	{
		while (i < argc)
		{
			new_args[i] = cmd->args[i];
			i++;
		}
		free(cmd->args);
	}
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	cmd->args = new_args;
	return (1);
}

void	append_command(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (!head || !new_cmd)
		return ;
	if (!*head)
	{
		*head = new_cmd;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
}

void	free_commands(t_cmd *head)
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->name);
		if (current->args)
		{
			i = 0;
			while (current->args[i])
				free(current->args[i++]);
			free(current->args);
		}
		free_redirections(current->redirections);
		free(current);
		current = next;
	}
}
