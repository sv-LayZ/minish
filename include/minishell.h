/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:58:52 by mregnaut          #+#    #+#             */
/*   Updated: 2025/10/16 10:53:27 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "builtin.h"
# include "parsing.h"

# define ENV_SEPARATOR ':'
# define ENV_PATH "PATH"

# define ERROR_MEMORY "Memory allocation error"
# define ERROR_READING_DIR "Error reading directory"

extern int	g_exit_status;

typedef struct s_expand_data
{
	char	**result;
	size_t	*j;
	size_t	*result_size;
}	t_expand_data;

/* SIGNALS */
void	setup_sigint(void);
void	setup_sigquit(void);
void	handle_sigint(int sig);
void	handle_signals(void);
/* PARSING */
char	*reader(void);
void	print_commands(t_cmd *cmds);

/* EXECUTION */
int		execute_command(t_cmd *cmd);
int		execute_pipeline(t_cmd *cmd);
int		setup_input_redirection(t_cmd *cmd);
int		setup_output_redirection(t_cmd *cmd);
int		apply_redirections(t_redir *redirections);
int		is_builtin(char *cmd);
int		execute_builtin(int builtin_index, char **args);
int		execute_external_command(char **args);
int		execute_with_redirections(t_cmd *cmd);
int		execute_builtin_with_redirections(t_cmd *cmd, int builtin_index);
int		execute_external_with_redirections(t_cmd *cmd);
char	*find_executable_in_path(char *cmd);


/* EXECUTABLE */
t_list	*get_files_in_dir(char *path);
char	*get_executable_path(char *str);
void	free_paths(char **paths);
int		check_file_in_list(t_list *files, char *str);

/* EXPAND_VARIABLES */
char	*expand_variables(const char *line);
char	*expand_exit_status(char **result, size_t *j, size_t *result_size);
int		handle_dollar_sign(const char *line, size_t *i, t_expand_data *data);

#endif
