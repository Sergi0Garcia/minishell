/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_cmd_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:43:12 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/04 09:16:58 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Function that cill insert element at the end of stack */
void	ft_cunshift(t_csb *stack, t_ci info)
{
	t_c	*new;

	new = (t_c *)malloc(sizeof(t_c));
	if (new == NULL)
		error("Error \n");
	new->ci = info;
	if (stack->tail == NULL)
	{
		new->next = NULL;
		new->prev = NULL;
		stack->tail = new;
		stack->head = new;
	}
	else
	{
		new->next = NULL;
		new->prev = stack->tail;
		stack->tail->next = new;
		stack->tail = new;
	}
	stack->size++;
	return ;
}

/* Add a new node at the top into existing double link list */
void	ft_cpush(t_csb *stack, t_ci info)
{
	t_c	*new;

	new = (t_c *)malloc(sizeof(t_c));
	if (new == NULL)
		error("Error \n");
	new->ci = info;
	new->next = stack->head;
	new->prev = NULL;
	if (stack->tail == NULL)
	{
		stack->tail = new;
		stack->head = new;
	}
	else
	{
		stack->head->prev = new;
		stack->head = new;
	}
	stack->size++;
	return ;
}

/* pop top element of a stack into doubly linked list */
t_ci	ft_cpop(t_csb *stack)
{
	t_ci	info;
	t_c		*tmp;

	if (stack->head == NULL)
		error("Error \n");
	info = stack->head->ci;
	tmp = stack->head;
	if (stack->head->next == NULL)
	{
		stack->head = NULL;
		stack->tail = NULL;
	}
	else
	{
		stack->head = stack->head->next;
		stack->head->prev = NULL;
	}
	if (stack->head != NULL)
		stack->head->prev = NULL;
	stack->size--;
	free(tmp);
	return (info);
}

/* shift removes the last item into the stack  */
t_ci	ft_cshift(t_csb *stack)
{
	t_ci	li;
	t_c		*tmp;

	if (stack->tail == NULL)
		error("Error \n");
	li = stack->tail->ci;
	tmp = stack->tail;
	if (stack->tail->prev != NULL)
		stack->tail = stack->tail->prev;
	if (stack->tail == NULL)
		stack->head = NULL;
	else if (stack->tail->next != NULL)
		stack->tail->next = NULL;
	stack->size--;
	if (stack->size == 1)
		stack->head = stack->tail;
	if (stack->size == 0)
	{
		stack->head = NULL;
		stack->tail = NULL;
	}
	free(tmp);
	return (li);
}

/* Function that duplicate a stack bundle */
t_csb	duplicate_csb(t_csb *stack)
{
	t_csb	new;
	t_c		*current;

	init_tcsb(&new);
	current = stack->head;
	if (current == NULL)
		return (new);
	while (current != NULL && current->next != NULL)
	{
		ft_cunshift(&new, current->ci);
		current = current->next;
	}
	ft_cunshift(&new, current->ci);
	return (new);
}
