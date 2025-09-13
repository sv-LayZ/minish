/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/08/22 15:31:07 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int apply_one_redir(t_redir *r)
{
	int fd;

	if (r->type == R_IN)
	{
		fd = open(r->filename, O_RDONLY);
		if (fd == -1)
		{
			perror(r->filename);
			return (-1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			return (-1);
		}
		close(fd);
	}
	else if (r->type == R_OUT_TRUNC || r->type == R_OUT_APPEND)
	{
		int flags = O_WRONLY | O_CREAT;
		if (r->type == R_OUT_APPEND)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd = open(r->filename, flags, 0644);
		if (fd == -1)
		{
			perror(r->filename);
			return (-1);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			return (-1);
		}
		close(fd);
	}
	else if (r->type == R_HEREDOC)
	{
		ft_putstr_fd("minishell: heredoc not implemented yet\n", 2);
		return (-1);
	}
	return (0);
}

int apply_ordered_redirs(t_cmd *cmd)
{
	t_redir *r;

	r = cmd->redirs;
	while (r)
	{
		if (apply_one_redir(r) == -1)
			return (-1);
		r = r->next;
	}
	return (0);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			break ;
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (full_path && access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*find_executable_in_path(char *cmd)
{
	char	**paths;
	char	*path_env;
	char	*result;

	if (!cmd || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, cmd);
	free_string_array(paths);
	return (result);
}

int	setup_input_redirection(t_cmd *cmd)
{
	int	fd;

	if (!cmd->input_file)
		return (0);
	if (cmd->heredoc)
	{
		ft_putstr_fd("minishell: heredoc not implemented yet\n", 2);
		return (-1);
	}
	fd = open(cmd->input_file, O_RDONLY);
	if (fd == -1)
	{
		perror(cmd->input_file);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	setup_output_redirection(t_cmd *cmd)
{
	int	fd;
	int	flags;

	if (!cmd->output_file)
		return (0);
	flags = O_WRONLY | O_CREAT;
	if (cmd->append_output)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(cmd->output_file, flags, 0644);
	if (fd == -1)
	{
		perror(cmd->output_file);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
