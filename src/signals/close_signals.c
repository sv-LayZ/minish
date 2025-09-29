#include "../include/minishell.h"

void close_sig(void)
{
	struct sigaction	old_sigint, old_sigquit;

	sigaction(SIGINT, NULL, &old_sigint);
	sigaction(SIGQUIT, NULL, &old_sigquit);
}