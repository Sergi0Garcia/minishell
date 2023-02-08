/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_signals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 04:49:46 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/07 06:30:34 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_quit_from_child(int sig, siginfo_t *info, void *context)
{
	(void) sig;
	(void) context;
	(void) info;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	sig_int(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(struct sigaction));
	sigemptyset(&(act.sa_mask));
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &sig_quit_from_child;
	sigaction(SIGINT, &act, NULL);
	return ;
}
