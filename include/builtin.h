/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:35:47 by mregnaut          #+#    #+#             */
/*   Updated: 2025/10/02 01:05:56 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

# define BUILTIN_CMDS "echo", "cd", "pwd", "export", "unset", "env", "exit", NULL
# define BUILTIN_FUNCS builtin_echo, builtin_cd, builtin_pwd, builtin_export, builtin_unset, builtin_env, NULL, NULL

/* Builtin function declarations */
int	builtin_echo(char **args);
int	builtin_cd(char **args);
int	builtin_pwd(char **args);
int	builtin_export(char **args);
int	builtin_unset(char **args);
int	builtin_env(char **args);
int	builtin_exit(char **args, t_cmd *cmds_head);

/* Utility functions */
int	is_builtin(char *cmd);
int	execute_builtin(int index, char **args, t_cmd *cmds_head);
int	is_valid_identifier(char *arg);
int	set_env_var(char *arg);
int	set_var_with_value(char *arg, char *equal_pos);
int	print_export_error(char *arg);
int	set_var_without_value(char *arg);

#endif
