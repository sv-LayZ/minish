/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:00:00 by assistant         #+#    #+#             */
/*   Updated: 2025/08/22 15:31:08 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_commands(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

static void	close_pipe_fds(int pipes[][2], int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pipes[i][0] != -1)
			close(pipes[i][0]);
		if (pipes[i][1] != -1)
			close(pipes[i][1]);
		i++;
	}
}

static int	setup_pipe_redirections(int pipes[][2],
	int cmd_index, int total_cmds)
{
	if (cmd_index > 0)
	{
		if (dup2(pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (-1);
		}
	}
	if (cmd_index < total_cmds - 1)
	{
		if (dup2(pipes[cmd_index][1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (-1);
		}
	}
	return (0);
}

static int	execute_piped_command(t_cmd *cmd, int pipes[][2],
	int cmd_index, int total_cmds)
{
	pid_t	pid;
	int		builtin_index;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		if (setup_pipe_redirections(pipes, cmd_index, total_cmds) == -1)
			exit(1);
		close_pipe_fds(pipes, total_cmds - 1);
		if (cmd->redirs && apply_ordered_redirs(cmd) == -1)
			exit(1);
		else if (!cmd->redirs)
		{
			if (setup_input_redirection(cmd) == -1
				|| setup_output_redirection(cmd) == -1)
				exit(1);
		}
		builtin_index = is_builtin(cmd->args[0]);
		if (builtin_index != -1)
			exit(execute_builtin(builtin_index, cmd->args));
		else
			exit(execute_external_command(cmd->args));
	}
	return (pid);
}

int	execute_pipeline(t_cmd *cmd)
{
	int		total_cmds;
	int		pipes[256][2];
	pid_t	pids[256];
	int		i;
	int		status;
	int		last_status;
	t_cmd	*current;

	total_cmds = count_commands(cmd);
	if (total_cmds == 1 && !cmd->next)
		return (execute_command(cmd));
	i = 0;
	while (i < total_cmds - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			while (--i >= 0)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
			}
			return (1);
		}
		i++;
	}
	current = cmd;
	i = 0;
	while (current && i < total_cmds)
	{
		pids[i] = execute_piped_command(current, pipes, i, total_cmds);
		if (pids[i] == -1)
		{
			close_pipe_fds(pipes, total_cmds - 1);
			return (1);
		}
		current = current->next;
		i++;
	}
	close_pipe_fds(pipes, total_cmds - 1);
	last_status = 0;
	i = 0;
	while (i < total_cmds)
	{
		if (waitpid(pids[i], &status, 0) != -1)
		{
			if (i == total_cmds - 1)
			{
				if (WIFEXITED(status))
					last_status = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					last_status = 128 + WTERMSIG(status);
			}
		}
		i++;
	}
	return (last_status);
}