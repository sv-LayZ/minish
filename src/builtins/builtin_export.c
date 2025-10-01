/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:35:47 by mregnaut          #+#    #+#             */
/*   Updated: 2025/10/02 01:02:48 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

extern char	**environ;

static void	print_exported_vars(void)
{
	int		i;
	char	*equal_pos;

	i = 0;
	while (environ[i])
	{
		printf("declare -x ");
		equal_pos = ft_strchr(environ[i], '=');
		if (equal_pos)
		{
			*equal_pos = '\0';
			printf("%s=\"%s\"\n", environ[i], equal_pos + 1);
			*equal_pos = '=';
		}
		else
			printf("%s\n", environ[i]);
		i++;
	}
}
/* l48-Just declaring a variable without value */

int	set_var_without_value(char *arg)
{
	if (setenv(arg, "", 1) != 0)
	{
		perror("export");
		return (1);
	}
	return (0);
}

int	set_var_with_value(char *arg, char *equal_pos)
{
	char	*key;
	char	*value;

	key = ft_substr(arg, 0, equal_pos - arg);
	value = equal_pos + 1;
	if (!key)
		return (1);
	if (setenv(key, value, 1) != 0)
	{
		perror("export");
		free(key);
		return (1);
	}
	free(key);
	return (0);
}

int	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	builtin_export(char **args)
{
	int	i;
	int	ret;

	if (!args[1])
	{
		print_exported_vars();
		return (0);
	}
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (set_env_var(args[i]) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}
