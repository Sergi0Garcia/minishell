/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:58:41 by rkanmado          #+#    #+#             */
/*   Updated: 2022/12/06 21:05:39 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init(t_minish *sh, char **argv)
{
	int		i;
	pid_t	pid;
	char	*str;

	i = 0;
	sh->argv = argv;
	pid = getpid();
	sh->interactive = false;
	str = ft_itoa(pid);
	sh->pid = str;
	sh->line = NULL;
	return ;
}

void	init_twsb(t_wsb *wsb)
{
	wsb->head = NULL;
	wsb->tail = NULL;
	wsb->size = 0;
	return ;
}
