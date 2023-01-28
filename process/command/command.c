/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:03:58 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/27 22:43:26 by rkanmado         ###   ########.fr       */
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
	init_tcsb(&list);
	while (token != NULL)
	{
		if (is_which_wt(token->wi.word) == PIPE || token->next == NULL)
		{
			if (token->next == NULL)
				add_to_chunk(&chunk, token->wi);
			handle_pipe_found(&list, &chunk);
			if (token->next == NULL)
				break ;
			token = token->next;
		}
		add_to_chunk(&chunk, token->wi);
		token = token->next;
	}
	return ;
}

void	add_to_chunk(t_wsb *chunk, t_wi wi)
{
	if (is_option(wi.word) && !is_opt_already_exits(chunk, wi.word))
		ft_wunshift(chunk, wi);
	else if (!is_option(wi.word))
		ft_wunshift(chunk, wi);
	return ;
}

void	handle_pipe_found(t_csb *list, t_wsb *wsb)
{
	parse_wsb_to_cmd(list, wsb);
	wsb->size = 0;
	free_stack(&wsb->head, &wsb->tail);
	return ;
}

void	parse_wsb_to_cmd(t_csb *list, t_wsb *wsb)
{
	t_w		*head;
	t_ci	ci;

	head = wsb->head;
	ci.args = "";
	ci.outfile = 0;
	ci.opts = "";
	ci.infile = 0;
	ci.name = "";
	while (head != NULL)
	{
		add_to_cmd(&head, &ci);
		head = head->next;
	}
	ft_cunshift(list, ci);
	return ;
}

void	add_to_cmd(t_w **head, t_ci *ci)
{
	t_w	*tmp;

	tmp = *head;
	if (tmp->prev == NULL)
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
		if (ft_strlen(ci->args) != 0)
			ci->args = ft_strjoin(ci->args, " ");
		ci->args = ft_strjoin(ci->args, tmp->wi.word);
	}
}
