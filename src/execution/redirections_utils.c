/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:49:19 by dedme             #+#    #+#             */
/*   Updated: 2025/10/02 19:30:45 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parent_builtin(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (128 + WTERMSIG(status));
}

void	child_builtin(t_cmd *cmd, int builtin_index)
{
	int	exit_code;

	if (cmd->redirections && apply_redirections(cmd->redirections) == -1)
	{
		free_commands(cmd);
		exit(1);
	}
	exit_code = execute_builtin(builtin_index, cmd->args, cmd);
	free_commands(cmd);
	exit(exit_code);
}
