/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 05:28:08 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/02 04:38:08 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_status;

void	sigreset(int sig, siginfo_t *info, void *context)
{
	(void) sig;
	(void) context;
	(void) info;
	if (sig == SIGINT)
	{
		g_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	return ;
}

void	sigexit(int sig, siginfo_t *info, void *context)
{
	(void) sig;
	(void) context;
	write(1, "exit\n", 6);
	kill(info->si_pid, SIGKILL);
	return ;
}

void	ignore_sigquit(void)
{
	struct sigaction	act;

	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}


void	h_exit(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &sigexit;
	sigaction(SIGQUIT, &sa, NULL);
	return ;
}

/* interactive mode signal handling */
void	interactive_mode_sig(void)
{
	struct sigaction	sa_res;

	ignore_sigquit();
	sa_res.sa_flags = SA_SIGINFO;
	sa_res.sa_sigaction = &sigreset;
	sigaction(SIGINT, &sa_res, NULL);
	return ;
}
