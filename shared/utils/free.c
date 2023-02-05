/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 02:21:58 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/05 11:41:59 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Function to freeze stack */
void	free_wsb(void **head, void **tail)
{
	t_w	*tmp;

	if (*head == NULL)
		return ;
	tmp = *head;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		free(tmp->prev);
	}
	free(tmp);
	*head = NULL;
	*tail = NULL;
	return ;
}

/* Function to freeze stack */
void	free_csb(void **head, void **tail)
{
	t_c	*tmp;

	if (*head == NULL)
		return ;
	tmp = *head;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		free(tmp->prev);
	}
	free(tmp);
	*head = NULL;
	*tail = NULL;
	return ;
}

void	free_kvp(t_kvp *kvp)
{
	int	i;

	i = 0;
	while (i < 13)
	{
		free(kvp[i].values.curr);
		free(kvp[i].values.next);
		i++;
	}
	free(kvp);
	return ;
}

void	free_env_list(t_env **env_lst)
{
	t_env	*tmp;

	while (env_lst && *env_lst)
	{
		tmp = (*env_lst)->next;
		free((*env_lst)->name);
		free((*env_lst)->value);
		free((*env_lst));
		*env_lst = tmp;
	}
	*env_lst = NULL;
}

void	free_all(t_minish *sh, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		if (i == 0)
		{
			printf("free pid");
			free(sh->pid);
		}
		if (i == 1)
		{
			printf("free env");
			free_env_list(&sh->env_lst);
		}
		if (i == 2)
			printf("free kpv");
		if (i == 3 && sh->wsb.size > 0)
		{
			free_wsb((void **) &sh->wsb.head, \
			(void **) &sh->wsb.tail);
		}
		if (i == 4 && sh->cmds.size > 0)
		{
			free_wsb((void **) &sh->cmds.head, \
			(void **) &sh->cmds.tail);
		}
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
		if (i == 0 && sh->wsb.size > 0)
		{
			free_wsb((void **) &sh->wsb.head, \
			(void **) &sh->wsb.tail);
		}
		if (i == 1 && sh->cmds.size > 0)
		{
			free_csb((void **) &sh->cmds.head, \
			(void **) &sh->cmds.tail);
		}
		i++;
	}
	return ;
}
