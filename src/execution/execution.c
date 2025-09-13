/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:50:01 by Hadia             #+#    #+#             */
/*   Updated: 2025/07/31 22:34:31 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_command(t_cmd *cmd)
{
	int	builtin_index;
	int	exit_code;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (cmd->input_file || cmd->output_file)
		return (execute_with_redirections(cmd));
	builtin_index = is_builtin(cmd->args[0]);
	if (builtin_index != -1)
		exit_code = execute_builtin(builtin_index, cmd->args);
	else
		exit_code = execute_external_command(cmd->args);
	return (exit_code);
}
