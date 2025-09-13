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

# define ENV_SEPARATOR ':'
# define ENV_PATH "PATH"

# define ERROR_MEMORY "Memory allocation error"
# define ERROR_READING_DIR "Error reading directory"

# define _POSIX_C_SOURCE 200809L

typedef struct s_expand_data
{
	char	**result;
	size_t	*j;
	size_t	*result_size;
}	t_expand_data;

// /* **********************************SIGNALS**************************************** */
void setup_sigint(void);
void setup_sigquit(void);
void handle_sigint(int sig);
void handle_signals(void);
// /* **********************************PARSING**************************************** */
char	*reader(void);
void print_commands(t_cmd *cmds);

// /* **********************************EXECUTION************************************ */
int	execute_command(t_cmd *cmd);
int	execute_pipeline(t_cmd *cmd);
int	setup_input_redirection(t_cmd *cmd);
int	setup_output_redirection(t_cmd *cmd);
int	apply_ordered_redirs(t_cmd *cmd);
int	is_builtin(char *cmd);
int	execute_builtin(int builtin_index, char **args);
int	execute_external_command(char **args);
int	execute_with_redirections(t_cmd *cmd);
char	*find_executable_in_path(char *cmd);

// Global variable for exit status ($?)
extern int g_exit_status;

// typedef struct s_cmd
// {
//     char *name;
//     char **args;
//     int heredoc; // 0 for no heredoc, 1 for heredoc
//     char *input_file;
//     char *output_file;
//     int append_output; // 0 for overwrite, 1 for append
//     struct s_cmd *next; // Pointer to the next command in a pipeline
// } t_cmd;

// typedef enum e_token_type
// {
//     TOKEN_PIPE,
//     TOKEN_REDIRECT_OUT,
//     TOKEN_REDIRECT_IN,
//     TOKEN_ENV_VAR,
//     TOKEN_COMMAND,
//     TOKEN_ARGUMENT,
//     TOKEN_REDIRECT_APPEND,
//     TOKEN_HEREDOC,
//     TOKEN_FILE,
//     TOKEN_OTHER
// } t_token_type;

// typedef enum e_quote_type
// {
//     SINGLE_QUOTE,
//     DOUBLE_QUOTE,
//     NO_QUOTE
// } t_quote_type;

// typedef struct s_operator_map
// {
//     char *op_str;
//     t_token_type type;
// } t_operator_map;

// typedef struct t_token
// {
//     t_token_type type;
//     char *value;
//     t_quote_type quote_type;
//     struct t_token *next; // Pointer to the next token in the linked list
//     struct t_token *prev; // Pointer to the previous token in the linked list
// } t_token;

// // /* **********************************PARSING**************************************** */
// char	*reader(void);
// int history_process(char *line);
// char *expand_variables(const char *line);


// // /* **********************************UTILS**************************************** */


// // /* **********************************LEXING**************************************** */

// t_token_type get_token_type(const char *value);
// t_token *create_token(t_token_type type, const char *value, int quoted);
// void append_token(t_token **head, t_token *new_tok);
// int operator_token_length(const char *str);
// char *extract_token(const char *input, int *index);
// int is_operator_char(char c);
// t_token *new_token(const char *value, t_quote_type quoted);
// t_token_type get_redirection_type(const char *line);
// t_token_type get_operator_type(const char *line);
// void free_tokens(t_token *head);

// // /* **********************************PARSE**************************************** */
// int is_argument_type(t_token_type type);
// int is_redirection(t_token_type type);
// char **ft_split_str(char const *s, char *delimiters);
// int add_arg(t_cmd *cmd, char *arg);
// void append_command(t_cmd **head, t_cmd *new_cmd);
// t_cmd *new_command(void);
// t_cmd *parse_tokens(t_token *tokens);
// t_token *line_lexer(const char *line);

/* **********************************EXECUTION******************************** */
char	*find_executable_in_path(char *cmd);
int		setup_input_redirection(t_cmd *cmd);
int		setup_output_redirection(t_cmd *cmd);
int		execute_external_command(char **args);
int		execute_builtin_with_redirections(t_cmd *cmd, int builtin_index);
int		execute_external_with_redirections(t_cmd *cmd);
int		execute_with_redirections(t_cmd *cmd);
int		execute_command(t_cmd *cmd);

/* **********************************EXECUTABLE******************************* */
t_list	*get_files_in_dir(char *path);
char	*get_executable_path(char *str);
void	free_paths(char **paths);
int		check_file_in_list(t_list *files, char *str);

/* **********************************EXPAND_VARIABLES************************* */
char	*expand_variables(const char *line);
char	*expand_exit_status(char **result, size_t *j, size_t *result_size);
int		handle_dollar_sign(const char *line, size_t *i, t_expand_data *data);

#endif
