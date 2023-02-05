/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 02:21:58 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/05 12:33:35 by rkanmado         ###   ########.fr       */
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
		// free(wtmp->wi.word);
		wtmp = wtmp->next;
		free(wtmp->prev);
	}
	free(wtmp);
	wsb->head = NULL;
	wsb->head = NULL;
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
		// free(ctmp->ci.args);
		// free(ctmp->ci.name);
		// free(ctmp->ci.opts);
		free(ctmp->prev);
	}
	free(ctmp);
	csb->head = NULL;
	csb->head = NULL;
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
			printf("feee");
		if (i == 2)
			printf("feee");
		if (i == 3 && sh->wsb.size > 0)
			free_wsb(&sh->wsb);
		if (i == 4 && sh->cmds.size > 0)
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
		if (i == 1 && sh->wsb.size > 0)
			free_wsb(&sh->wsb);
		if (i == 2 && sh->cmds.size > 0)
			free_csb(&sh->cmds);
		i++;
	}
	return ;
}
