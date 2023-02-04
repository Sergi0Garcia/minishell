/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 05:28:08 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/04 21:30:38 by segarcia         ###   ########.fr       */
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
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

int	remove_echoback(t_b echo_ctl_chr)
{
	struct termios	terminos_p;
	int				status;

	(void)echo_ctl_chr;
	status = tcgetattr(STDOUT_FILENO, &terminos_p);
	if (status == -1)
		return (1);
	terminos_p.c_lflag &= ~(ECHOCTL);
	status = tcsetattr(STDOUT_FILENO, TCSANOW, &terminos_p);
	if (status == -1)
		return (1);
	return (0);
}

void	ignore_sigquit(void)
{
	struct sigaction	act;

	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
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
