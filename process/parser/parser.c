/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 00:50:29 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/17 04:43:41 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_b	parser(t_minish *sh)
{
	int		i;
	t_w		*word;
	t_kvp	*kvp;
	t_b		can_continue;

	i = 0;
	kvp = get_kv_pairs();
	word = sh->wsb.head;
	can_continue = true;
	while (word != NULL && can_continue)
	{
		if (word->wi.sep != SPACE)
		{
			if (i == 0)
				is_edges_good(word, BEGINING, kvp, &can_continue);
			else if (i == sh->wsb.size - 1)
				is_edges_good(word, END, kvp, &can_continue);
			else
				is_between_good(word, kvp, &can_continue);
		}
		word = word->next;
		i++;
	}
	return (can_continue);
}

t_b	is_edges_good(t_w *word, t_wt key, t_kvp *kvp, t_b *can_continue)
{
	t_b		is_curr_exist;
	t_cn	cn;

	cn = get_values_of_index(key, kvp);
	is_curr_exist = is_wt_between_values(word->wi.sep, cn.curr);
	if (is_curr_exist)
		return (true);
	else
	{
		*can_continue = false;
		parser_error(char_of_sep(word->wi.sep));
	}
	return (false);
}

t_cn	set_wt_values(t_wt *curr, t_wt *next, t_cn *cn)
{
	cn->curr = curr;
	cn->next = next;
	return (*cn);
}

t_b	is_between_good(t_w *word, t_kvp *kvp, t_b *can_continue)
{
	t_b		is_next_exist;
	t_cn	cn;

	cn = get_values_of_index(word->wi.sep, kvp);
	is_next_exist = is_wt_between_values(word->next->wi.sep, cn.curr);
	if (is_next_exist)
		return (true);
	else
	{
		*can_continue = false;
		parser_error(char_of_sep(word->next->wi.sep));
	}
	return (false);
}
