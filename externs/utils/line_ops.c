/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:03:36 by rkanmado          #+#    #+#             */
/*   Updated: 2022/11/26 17:22:51 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Function that will insert element at the end of stack */
void	ft_unshift_line(t_lsb *stack, t_sli info)
{
	t_ls	*new;

	new = (t_ls *)malloc(sizeof(t_ls));
	if (new == NULL)
		error("Error \n");
	new->li = info;
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
void	ft_push_line(t_lsb *stack, t_sli info)
{
	t_ls	*new;

	new = (t_ls *)malloc(sizeof(t_ls));
	if (new == NULL)
		error("Error \n");
	new->li = info;
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
t_sli	ft_pop_line(t_lsb *stack)
{
	t_sli	info;
	t_ls	*tmp;

	if (stack->head == NULL)
		error("Error \n");
	info = stack->head->li;
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
t_sli	ft_shift_line(t_lsb *stack)
{
	t_sli	li;
	t_ls	*tmp;

	if (stack->tail == NULL)
		error("Error \n");
	li = stack->tail->li;
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
