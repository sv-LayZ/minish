/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/10/02 01:50:41 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

static void	write_heredoc_lines(int fd, char *delimiter, int expand)
{
	char	*line;
	char	*expanded;

	line = readline("> ");
	while (line)
	{
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			return ;
		}
		if (expand)
		{
			expanded = expand_variables(line);
			if (expanded)
				ft_putendl_fd(expanded, fd);
			else
				ft_putendl_fd(line, fd);
			free(expanded);
		}
		else
			ft_putendl_fd(line, fd);
		free(line);
		line = readline("> ");
	}
}

int	handle_heredoc(char *delimiter, int count, int expand)
{
	int		fd;
	char	*tmpfile;

	tmpfile = create_tmpfile(count);
	if (!tmpfile)
		return (perror("malloc malfunction"), -1);
	fd = open(tmpfile, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (perror("open heredoc"), free(tmpfile), -1);
	write_heredoc_lines(fd, delimiter, expand);
	close(fd);
	fd = open(tmpfile, O_RDONLY);
	if (fd == -1)
		return (perror("open heredoc read"),
			unlink(tmpfile), free(tmpfile), -1);
	unlink(tmpfile);
	return (free(tmpfile), fd);
}

static int	apply_one_redir(t_redir *r, int count)
{
	int	fd;

	if (r->type == TOKEN_REDIRECT_IN)
		return (redir_in(r->file));
	if (r->type == TOKEN_REDIRECT_OUT || r->type == TOKEN_REDIRECT_APPEND)
		return (redir_out(r->file, r->type));
	if (r->type == TOKEN_HEREDOC)
	{
		close_sig();
		fd = handle_heredoc(r->file, count, r->expand);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			return (-1);
		}
		close(fd);
	}
	return (0);
}

int	apply_redirections(t_redir *redirections)
{
	t_redir	*r;
	int		count;

	r = redirections;
	count = 0;
	while (r)
	{
		if (apply_one_redir(r, count++) == -1)
			return (-1);
		r = r->next;
	}
	return (0);
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
