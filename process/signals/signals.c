/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 05:28:08 by rkanmado          #+#    #+#             */
/*   Updated: 2022/12/06 22:27:25 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigreset(int sig, siginfo_t *info, void *context)
{
	(void) sig;
	(void) context;
	if (info->si_signo == SIGINT)
		write(1, "\n", 1);
	if (info->si_signo == SIGQUIT)
		exit(EXIT_SUCCESS);
	return ;
}

void	quit(int sig, siginfo_t *info, void *context)
{
	(void) sig;
	(void) context;
	write(1, "\n", 1);
	kill(info->si_pid, SIGKILL);
	return ;
}

void	h_quit(void)
{
	struct sigaction	sa;

	sa.sa_flags = SIGINFO;
	sa.sa_sigaction = &quit;
	sigaction(SIGQUIT, &sa, NULL);
	return ;
}

/* interactive mode signal handling */
void	interactive_mode_sig(void)
{
	struct sigaction	sa;

	sa.sa_flags = SIGINFO;
	sa.sa_sigaction = &sigreset;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	return ;
}

/* non interactive mode signal handling */
void	no_interactive_mode_sig(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = NULL;
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	return ;
}
