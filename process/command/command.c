/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:03:58 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/25 05:02:54 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	generate_cmd(t_minish *sh)
{
	t_w		*token;
	t_csb	list;
	t_wsb	chunk;

	token = sh->wsb.head;
	init_twsb(&chunk);
	while (token != NULL)
	{
		add_to_chunk(&chunk, token->wi);
		if (is_which_wt(token->wi.word) == PIPE || token != NULL)
			handle_pipe_found(&list, &chunk);
		token = token->next;
	}
	return ;
}

void	add_to_chunk(t_wsb *chunk, t_wi wi)
{
	if (is_option(wi.word) && !is_opt_already_exits(chunk, wi.word))
		ft_wunshift(chunk, wi);
	return ;
}

void	handle_pipe_found(t_csb *list, t_wsb *wsb)
{
	parse_wsb_to_cmd(list, wsb);
	free_stack(&wsb->head, &wsb->tail);
	return ;
}

void	parse_wsb_to_cmd(t_csb *list, t_wsb *wsb)
{
	t_w		*head;
	int		counter;
	t_ci	ci;

	head = wsb->head;
	counter = 0;
	while (head == NULL)
	{
		add_to_cmd(&head, counter, &ci);
		head = head->next;
	}
	ft_cunshift(list, ci);
	return ;
}

void	add_to_cmd(t_w **head, int counter, t_ci *ci)
{
	t_w	*tmp;

	tmp = *head;
	if (counter == 0)
		ci->name = tmp->wi.word;
	else if (*tmp->wi.word == '-')
	{
		ci->opts = ft_strjoin(ci->opts, tmp->wi.word);
		ci->opts = ft_strjoin(ci->opts, " ");
	}
	else if (tmp->wi.sep == DLESS || tmp->wi.sep == LESS)
	{
		ci->infile = get_fd();
		tmp = tmp->next;
	}
	else if (tmp->wi.sep == DGREAT || tmp->wi.sep == GREAT)
	{
		ci->outfile = get_fd();
		tmp = tmp->next;
	}
	else
	{
		ci->args = ft_strjoin(ci->args, tmp->wi.word);
		ci->args = ft_strjoin(ci->args, " ");
	}
}
