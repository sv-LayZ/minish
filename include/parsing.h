/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:58:58 by mregnaut          #+#    #+#             */
/*   Updated: 2025/10/01 18:55:27 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "minishell.h"

/* DEBUGGING */
# define DEBUGGING 0

/* TOKEN TYPES */
typedef enum e_token_type
{
	TOKEN_PIPE,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_FILE,
	TOKEN_ENV_VAR,
	TOKEN_OTHER
}	t_token_type;

typedef enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quote_type;

/* TOKEN STRUCTURE */
typedef struct s_token
{
	t_token_type		type;
	char				*value;
	t_quote_type		quote_type;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

/* REDIRECTION STRUCTURE */
typedef struct s_redir
{
	t_token_type		type;
	char				*file;
	int					expand; /* 1 if heredoc content should expand variables, 0 otherwise */
	struct s_redir		*next;
}	t_redir;

/* COMMAND STRUCTURE */
typedef struct s_cmd
{
	char				*name;
	char				**args;
	t_redir				*redirections;
	struct s_cmd		*next;
}	t_cmd;

/* PARSING FUNCTIONS */
t_token		*lexer(const char *line);
t_cmd		*parser(t_token *tokens);
t_cmd		*parsing(char *line);
int			get_operator_length(const char *line, int i);
int			skip_whitespace(const char *line, int i);
char		*extract_word(const char *line, int start, int end);

/* TOKEN FUNCTIONS */
t_token		*create_token(t_token_type t, const char *v, t_quote_type q);
void		append_token(t_token **head, t_token *new_token);
void		free_tokens(t_token *head);
t_token_type get_token_type(const char *value);

/* COMMAND FUNCTIONS */
t_cmd		*create_command(void);
void		append_command(t_cmd **head, t_cmd *new_cmd);
void		free_commands(t_cmd *head);
int			add_argument(t_cmd *cmd, char *arg);

/* REDIRECTION FUNCTIONS */
t_redir		*create_redirection(t_token_type type, char *file, int expand);
void		append_redirection(t_redir **head, t_redir *new_redir);
void		free_redirections(t_redir *head);

/* UTILITY FUNCTIONS */
int			is_operator(char c);
int			is_redirection_token(t_token_type type);
char		*expand_variables(const char *str);

/* DEBUG FUNCTIONS */
void		debug_print_cmd(t_cmd *cmd);

#endif