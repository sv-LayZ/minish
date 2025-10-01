/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:45:00 by mregnaut          #+#    #+#             */
/*   Updated: 2025/10/01 18:09:31 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

char	*reader(void)
{
	char	*line;
	char	*prompt;

	prompt = NULL;
	if (isatty(STDIN_FILENO))
		prompt = "minishell$ ";
	line = readline(prompt);
	if (!line)
	{
		if (isatty(STDIN_FILENO))
			printf("exit\n");
		exit(g_exit_status);
	}
	return (line);
}
