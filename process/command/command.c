/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:03:58 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/02 04:52:01 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_b	generate_cmd(t_minish *sh)
{
	t_w		*token;
	t_wsb	chunk;
	int		i;

	token = sh->wsb.head;
	init_twsb(&chunk);
	init_tcsb(&sh->cmds);
	i = 1;
	while (token != NULL)
	{
		if (is_which_wt(token->wi.word) == PIPE || token->next == NULL)
		{
			if (token->next == NULL)
				add_to_chunk(&chunk, token->wi);
			if (!can_handle_pipe_found(&sh->cmds, &chunk, &i))
				return (false);
			if (token->next == NULL)
				break ;
			token = token->next;
			continue ;
		}
		add_to_chunk(&chunk, token->wi);
		token = token->next;
	}
	return (true);
}

void	add_to_chunk(t_wsb *chunk, t_wi wi)
{
	if (is_option(wi.word) && !is_opt_already_exits(chunk, wi.word))
		ft_wunshift(chunk, wi);
	else if (!is_option(wi.word))
		ft_wunshift(chunk, wi);
	return ;
}

t_b	can_handle_pipe_found(t_csb *list, t_wsb *wsb, int *i)
{
	if (!can_parse_wsb_to_cmd(list, wsb, i))
		return (false);
	wsb->size = 0;
	free_stack(&wsb->head, &wsb->tail);
	return (true);
}

t_b	can_parse_wsb_to_cmd(t_csb *list, t_wsb *wsb, int *i)
{
	t_w		*head;
	t_ci	ci;

	head = wsb->head;
	ci.args = "";
	ci.outfile = 1;
	ci.opts = "";
	ci.infile = 0;
	ci.name = "";
	while (head != NULL)
	{
		if (!can_add_to_cmd(&head, &ci, *i))
			return (false);
		head = head->next;
	}
	*i +=1;
	ft_cunshift(list, ci);
	return (true);
}

t_b	can_add_to_cmd(t_w **head, t_ci *ci, int i)
{
	t_w	*tmp;

	tmp = *head;
	if (tmp->prev == NULL)
		ci->name = tmp->wi.word;
	else if (*tmp->wi.word == '-')
		ci->opts = add_arg_or_opt(ci->opts, tmp->wi.word);
	else if (tmp->wi.sep == DLESS || tmp->wi.sep == LESS)
		return (handle_redirect(head, i, &ci->infile));
	else if (tmp->wi.sep == DGREAT || tmp->wi.sep == GREAT)
		return (handle_redirect(head, i, &ci->outfile));
	else
		ci->args = add_arg_or_opt(ci->args, tmp->wi.word);
	return (true);
}
