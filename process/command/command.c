/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:03:58 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/30 11:14:53 by segarcia         ###   ########.fr       */
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

t_b	can_handle_pipe_found(t_csb *list, t_wsb *wsb)
{
	if (!can_parse_wsb_to_cmd(list, wsb))
		return (false);
	wsb->size = 0;
	free_stack(&wsb->head, &wsb->tail);
	return (true);
}

t_b	can_parse_wsb_to_cmd(t_csb *list, t_wsb *wsb)
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
	if (tmp->prev == NULL)
		ci->name = tmp->wi.word;
	else if (*tmp->wi.word == '-')
		ci->opts = add_arg_or_opt(ci->opts, tmp->wi.word);
	else if (tmp->wi.sep == DLESS || tmp->wi.sep == LESS)
	{
		ci->infile = get_fd(tmp->next->wi.word, tmp->wi.sep);
		printf("infile %d\n", ci->infile);
		if (!can_increment_word(head))
			return (false);
	}
	else if (tmp->wi.sep == DGREAT || tmp->wi.sep == GREAT)
	{
		ci->outfile = get_fd(tmp->next->wi.word, tmp->wi.sep);
		printf("outfile %s\n", (*head)->next->wi.word);
		if (!can_increment_word(head))
			return (false);
	}
	else
		ci->args = add_arg_or_opt(ci->args, tmp->wi.word);
	return (true);
}
