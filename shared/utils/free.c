/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 02:21:58 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/07 13:27:32 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Function to freeze stack */
void	free_wsb(t_wsb *wsb)
{
	t_w		*wtmp;

	wsb->size = 0;
	if (wsb->head == NULL)
		return ;
	wtmp = wsb->head;
	while (wtmp->next != NULL)
	{
		wtmp = wtmp->next;
		free(wtmp->prev->wi.word);
		free(wtmp->prev);
	}
	free(wtmp->wi.word);
	free(wtmp);
	wsb->head = NULL;
	wsb->tail = NULL;
	return ;
}

/* Function to freeze stack */
void	free_csb(t_csb *csb)
{
	t_c		*ctmp;

	csb->size = 0;
	if (csb->head == NULL)
		return ;
	ctmp = csb->head;
	while (ctmp->next != NULL)
	{
		ctmp = ctmp->next;
		free(ctmp->prev->ci.args);
		free(ctmp->prev->ci.opts);
		free(ctmp->prev->ci.name);
		free(ctmp->prev);
	}
	free(ctmp->ci.args);
	free(ctmp->ci.opts);
	free(ctmp->ci.name);
	free(ctmp);
	csb->head = NULL;
	csb->tail = NULL;
	return ;
}

void	free_kvp(t_kvp **kvp)
{
	t_kvp	*tmp;

	tmp = *kvp;
	free(tmp);
	return ;
}

void	free_all(t_minish *sh, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		if (i == 0)
		{
			free(sh->pid);
			free(sh->line);
		}
		if (i == 1)
			free_kvp(&sh->kvp);
		if (i == 2)
			free_env_list(&sh->env_lst);
		if (i == 3)
			free_wsb(&sh->wsb);
		if (i == 4)
			free_csb(&sh->cmds);
		i++;
	}
	return ;
}

void	free_for_next_run(t_minish *sh, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		if (i == 0)
			free(sh->line);
		if (i == 1)
			free_wsb(&sh->wsb);
		if (i == 2)
			free_csb(&sh->cmds);
		i++;
	}
	return ;
}
