/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/08/22 15:31:06 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern char	**environ;

int	execute_builtin_with_redirections(t_cmd *cmd, int builtin_index)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		if (cmd->redirs)
		{
			if (apply_ordered_redirs(cmd) == -1)
				exit(1);
		}
		else
		{
			if (setup_input_redirection(cmd) == -1)
				exit(1);
			if (setup_output_redirection(cmd) == -1)
				exit(1);
		}
		exit(execute_builtin(builtin_index, cmd->args));
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (128 + WTERMSIG(status));
	}
}

static int	execute_child_with_redirections(t_cmd *cmd, char *executable_path)
{
	if (cmd->redirs)
	{
		if (apply_ordered_redirs(cmd) == -1)
			exit(1);
	}
	else
	{
		if (setup_input_redirection(cmd) == -1)
			exit(1);
		if (setup_output_redirection(cmd) == -1)
			exit(1);
	}
	if (execve(executable_path, cmd->args, environ) == -1)
	{
		perror("execve");
		free(executable_path);
		exit(127);
	}
	return (0);
}

static int	fork_and_execute_external(t_cmd *cmd, char *executable_path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(executable_path);
		return (1);
	}
	if (pid == 0)
		execute_child_with_redirections(cmd, executable_path);
	else
	{
		free(executable_path);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (128 + WTERMSIG(status));
	}
	return (0);
}

int	execute_external_with_redirections(t_cmd *cmd)
{
	char	*executable_path;

	executable_path = find_executable_in_path(cmd->args[0]);
	if (!executable_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	return (fork_and_execute_external(cmd, executable_path));
}

int	execute_with_redirections(t_cmd *cmd)
{
	int	builtin_index;

	builtin_index = is_builtin(cmd->args[0]);
	if (builtin_index != -1)
		return (execute_builtin_with_redirections(cmd, builtin_index));
	else
		return (execute_external_with_redirections(cmd));
}
