/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:58:41 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/24 11:23:51 by rkanmado         ###   ########.fr       */
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
	init_twsb(&sh->wsb);
	init_command(&sh->cmds);
	sh->line = NULL;
	return ;
}

void	init_command(t_cmd *cmds)
{
	cmds->cmd = NULL;
	cmds->content = NULL;
	return ;
}

void	init_twsb(t_wsb *wsb)
{
	wsb->head = NULL;
	wsb->tail = NULL;
	wsb->size = 0;
	return ;
}
