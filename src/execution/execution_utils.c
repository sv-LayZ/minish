/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/22 23:46:10 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

int handle_heredoc(char *delimiter)
{
	int     fd;
	char    *line;
	char    *tmpfile = "/tmp/minishell_heredoc";

	fd = open(tmpfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open heredoc");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);

	fd = open(tmpfile, O_RDONLY);
	if (fd == -1)
	{
		perror("open heredoc read");
		return (-1);
	}
	return (fd);
}

static int apply_one_redir(t_redir *r)
{
	int fd;

	if (r->type == TOKEN_REDIRECT_IN)
	{
		fd = open(r->file, O_RDONLY);
		if (fd == -1)
		{
			perror(r->file);
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
	else if (r->type == TOKEN_REDIRECT_OUT || r->type == TOKEN_REDIRECT_APPEND)
	{
		int flags = O_WRONLY | O_CREAT;
		if (r->type == TOKEN_REDIRECT_APPEND)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd = open(r->file, flags, 0644);
		if (fd == -1)
		{
			perror(r->file);
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
	else if (r->type == TOKEN_HEREDOC)
	{
		fd = handle_heredoc(r->file);
		if (fd == -1)
			return(-1);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			return (-1);
		}
	}
	return (0);
}

int apply_redirections(t_redir *redirections)
{
	t_redir *r;

	r = redirections;
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
	// This function is now handled by apply_redirections
	// Keep for compatibility but it's no longer used with new structure
	(void)cmd;
	return (0);
}

int	setup_output_redirection(t_cmd *cmd)
{
	// This function is now handled by apply_redirections
	// Keep for compatibility but it's no longer used with new structure
	(void)cmd;
	return (0);
}
