/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 05:28:08 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/29 05:51:17 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigreset(int sig, siginfo_t *info, void *context)
{
	(void) sig;
	(void) context;
	(void) info;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	sigquit(int sig, siginfo_t *info, void *context)
{
	(void) sig;
	(void) context;
	write(1, "exit\n", 6);
	kill(info->si_pid, SIGKILL);
	return ;
}

void	h_quit(void)
{
	struct sigaction	sa;

	sa.sa_flags = SIGINFO;
	sa.sa_sigaction = &sigquit;
	sigaction(SIGQUIT, &sa, NULL);
	return ;
}

/* interactive mode signal handling */
void	interactive_mode_sig(void)
{
	struct sigaction	sa_res;
	struct sigaction	sa_quit;

	sa_res.sa_flags = SA_SIGINFO;
	sa_res.sa_sigaction = &sigreset;
	sa_quit.sa_flags = SA_SIGINFO;
	sa_quit.sa_sigaction = &sigquit;
	sigaction(SIGINT, &sa_res, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
	return ;
}

/* non interactive mode signal handling */
void	no_interactive_mode_sig(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = NULL;
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	return ;
}
