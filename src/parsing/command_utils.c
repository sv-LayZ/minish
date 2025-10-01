/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:09:00 by mregnaut          #+#    #+#             */
/*   Updated: 2025/10/01 15:45:20 by dedme            ###   ########.fr       */
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

static int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}

static void	copy_args(char **dest, char **src, int argc)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		dest[i] = src[i];
		i++;
	}
}

int	add_argument(t_cmd *cmd, char *arg)
{
	char	**new_args;
	int		argc;

	if (!cmd || !arg)
		return (0);
	argc = count_args(cmd->args);
	new_args = malloc(sizeof(char *) * (argc + 2));
	if (!new_args)
		return (0);
	if (cmd->args)
	{
		copy_args(new_args, cmd->args, argc);
		free(cmd->args);
	}
	new_args[argc] = ft_strdup(arg);
	new_args[argc + 1] = NULL;
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
