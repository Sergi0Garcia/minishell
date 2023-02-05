/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_signals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 04:49:46 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/05 04:50:21 by segarcia         ###   ########.fr       */
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
	struct sigaction	sa_res;

	sa_res.sa_flags = SA_SIGINFO;
	sa_res.sa_sigaction = &sig_quit_from_child;
	sigaction(SIGINT, &sa_res, NULL);
	return ;
}
