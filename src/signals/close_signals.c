/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedme <dedme@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:58:06 by dedme             #+#    #+#             */
/*   Updated: 2025/10/01 15:59:05 by dedme            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_sig(void)
{
	struct sigaction	old_sigint;
	struct sigaction	old_sigquit;

	sigaction(SIGINT, NULL, &old_sigint);
	sigaction(SIGQUIT, NULL, &old_sigquit);
}
