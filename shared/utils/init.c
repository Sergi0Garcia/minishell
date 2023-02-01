/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:58:41 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/01 04:57:38 by rkanmado         ###   ########.fr       */
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
	sh->env_lst = NULL;
	str = ft_itoa(pid);
	sh->pid = str;
	init_twi(&sh->last);
	init_twsb(&sh->wsb);
	init_tcsb(&sh->cmds);
	sh->line = NULL;
	return ;
}

void	init_tcsb(t_csb *cmds)
{
	cmds->head = NULL;
	cmds->tail = NULL;
	cmds->size = 0;
	return ;
}

void	init_twsb(t_wsb *wsb)
{
	wsb->head = NULL;
	wsb->tail = NULL;
	wsb->size = 0;
	return ;
}

void	init_twi(t_wi *i)
{
	i->can_expand = false;
	i->sep = NEIN;
	i->quote = NONE;
	i->word = "\0";
	return ;
}
