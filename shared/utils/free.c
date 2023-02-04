/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 02:21:58 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/04 13:36:00 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_str(char **str)
{
	free(*str);
	return ;
}

/* Function to freeze stack */
void	free_stack(void **head, void **tail)
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
	return ;
}

void	free_all(t_minish *sh, int nbr)
{
	int	i;

	i = 0;

	while (i < nbr)
	{
		if (i == 0)
			free(sh->pid);
		if (i == 1)
			free_env_node(&sh->env_lst);
		if (i == 2)
			free_kvp(sh->kvp);
		if (i == 3)
			free_stack((void **) &sh->wsb.head, \
			(void **) &sh->wsb.tail);
		if (i == 4)
			free_stack((void **) &sh->cpy.head, \
			(void **) &sh->cpy.tail);
		if (i == 5)
			free_stack((void **) &sh->cmds.head, \
			(void **) &sh->cmds.tail);
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
			free_stack((void **) &sh->wsb.head, \
			(void **) &sh->wsb.tail);
		if (i == 1)
			free_stack((void **) &sh->cpy.head, \
			(void **) &sh->cpy.tail);
		if (i == 2)
			free_stack((void **) &sh->cmds.head, \
			(void **) &sh->cmds.tail);
		i++;
	}
	return ;
}
