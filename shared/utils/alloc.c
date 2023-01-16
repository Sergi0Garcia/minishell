/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 06:10:16 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/16 08:47:59 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_wt	*alloc(t_wt	**wt, int mem_nbr)
{
	*wt = malloc(sizeof(t_wt) * mem_nbr);
	if (*wt == NULL)
		error("Memory allocation failed");
	return (*wt);
}

void	*ft_cpywt(void *dst, const void *src, size_t n)
{
	const t_wt	*s;
	t_wt		*d;

	s = src;
	d = dst;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dst);
}

/* Function to freeze stack */
void	ft_free_stack(t_w **head, t_w **tail)
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
