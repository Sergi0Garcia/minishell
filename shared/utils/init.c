/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:58:41 by rkanmado          #+#    #+#             */
/*   Updated: 2022/11/29 23:56:17 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init(t_minish *sh, char **argv, char **env)
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

	while (env[i] != NULL)
		i++;
	sh->env = (char **) malloc((i + 1) * sizeof(char *));
	i = 0;
	while (env[i] != NULL)
	{
		sh->env[i] = ft_strdup(env[i]);
		i++;
	}
	return ;
}

void	init_twsb(t_wsb *wsb)
{
	wsb->head = NULL;
	wsb->tail = NULL;
	wsb->size = 0;
	return ;
}
