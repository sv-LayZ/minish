/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_external.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/07/31 22:34:26 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern char	**environ;

static int	execute_child_process(char *executable_path, char **args)
{
	if (execve(executable_path, args, environ) == -1)
	{
		perror("execve");
		free(executable_path);
		exit(127);
	}
	return (0);
}

static int	wait_for_child(pid_t pid, char *executable_path)
{
	int	status;

	free(executable_path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (128 + WTERMSIG(status));
}

int	execute_external_command(char **args)
{
	char	*executable_path;
	pid_t	pid;

	if (!args || !args[0])
		return (127);
	executable_path = find_executable_in_path(args[0]);
	if (!executable_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(executable_path);
		return (1);
	}
	if (pid == 0)
		execute_child_process(executable_path, args);
	else
		return (wait_for_child(pid, executable_path));
	return (0);
}
