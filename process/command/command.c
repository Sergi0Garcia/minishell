/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:03:58 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/05 11:57:19 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_b	generate_cmd(t_minish *sh)
{
	t_w		*token;
	t_wsb	chunk;

	token = sh->wsb.head;
	init_twsb(&chunk);
	init_tcsb(&sh->cmds);
	while (token != NULL)
	{
		if (is_which_wt(token->wi.word) == PIPE || token->next == NULL)
		{
			if (token->next == NULL)
				add_to_chunk(&chunk, token->wi);
			if (!can_handle_pipe_found(&sh->cmds, &chunk))
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
	if (is_option(wi.word))
		ft_wunshift(chunk, wi);
	else if (!is_option(wi.word))
		ft_wunshift(chunk, wi);
	return ;
}

t_b	can_handle_pipe_found(t_csb *list, t_wsb *wsb)
{
	if (!can_parse_wsb_to_cmd(list, wsb))
		return (false);
	wsb->size = 0;
	free_wsb(wsb);
	return (true);
}

t_b	can_parse_wsb_to_cmd(t_csb *list, t_wsb *wsb)
{
	t_w		*head;
	t_ci	ci;

	head = wsb->head;
	ci.args = NULL;
	ci.outfile = 1;
	ci.opts = NULL;
	ci.infile = 0;
	ci.name = NULL;
	while (head != NULL)
	{
		if (!can_add_to_cmd(&head, &ci))
			return (false);
		head = head->next;
	}
	ft_cunshift(list, ci);
	return (true);
}

t_b	can_add_to_cmd(t_w **head, t_ci *ci)
{
	t_w	*tmp;

	tmp = *head;
	if (tmp->prev == NULL && tmp->wi.sep != DLESS)
		ci->name = tmp->wi.word;
	else if (*tmp->wi.word == '-' && can_add_opt(ci->args))
		ci->opts = add_arg_or_opt(ci->opts, tmp->wi);
	else if (tmp->wi.sep == DLESS || tmp->wi.sep == LESS)
		return (handle_redirect(head, &ci->infile));
	else if (tmp->wi.sep == DGREAT || tmp->wi.sep == GREAT)
		return (handle_redirect(head, &ci->outfile));
	else
		ci->args = add_arg_or_opt(ci->args, tmp->wi);
	return (true);
}
