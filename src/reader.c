/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregnaut <mregnaut@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:45:00 by mregnaut          #+#    #+#             */
/*   Updated: 2025/09/15 20:45:00 by mregnaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*reader(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (!line)
	{
		printf("exit\n");
		exit(g_exit_status);
	}
	return (line);
}