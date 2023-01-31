/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 00:50:29 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/30 03:56:43 by rkanmado         ###   ########.fr       */
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
		if (word->wi.sep != SPACES)
		{
			if (i == 0)
			{
				is_begin_good(word, kvp, &can_continue);
				if (sh->wsb.size > 1)
					is_between_good(word, kvp, &can_continue);
			}
			else if (i == sh->wsb.size - 1)
				is_end_good(word, kvp, &can_continue);
			else
				is_between_good(word, kvp, &can_continue);
		}
		word = word->next;
		i++;
	}
	return (can_continue);
}

void	handle_parser_err(t_w *word, t_b is_curr, t_b is_next, \
		t_b *can_continue)
{
	*can_continue = false;
	if (!is_next)
		parser_error(char_of_sep(word->next->wi.sep));
	else if (!is_curr)
		parser_error(char_of_sep(word->wi.sep));
	return ;
}

t_b	is_begin_good(t_w *word, t_kvp *kvp, t_b *can_continue)
{
	t_b		is_curr;
	t_cn	cn1;

	cn1 = get_values_of_index(BEGINING, kvp);
	is_curr = is_wt_between_values(word->wi.sep, cn1.curr);
	if (is_curr)
		return (true);
	handle_parser_err(word, is_curr, true, can_continue);
	return (false);
}

t_b	is_end_good(t_w *word, t_kvp *kvp, t_b *can_continue)
{
	t_b		is_curr;
	t_cn	cn;

	if (word->wi.sep == GREAT || word->wi.sep == DGREAT \
		|| word->wi.sep == LESS || word->wi.sep == DLESS)
		return (true);
	cn = get_values_of_index(END, kvp);
	is_curr = is_wt_between_values(word->wi.sep, cn.next);
	if (is_curr)
		return (true);
	else
	{
		*can_continue = false;
		parser_error(char_of_sep(word->wi.sep));
	}
	return (false);
}

t_b	is_between_good(t_w *word, t_kvp *kvp, t_b *can_continue)
{
	t_b		is_next;
	t_b		is_curr;
	t_cn	cn1;
	t_cn	cn2;

	cn1 = get_values_of_index(word->wi.sep, kvp);
	cn2 = get_values_of_index(word->next->wi.sep, kvp);
	is_curr = is_wt_between_values(word->next->wi.sep, cn1.curr);
	if (word->next == NULL)
		is_next = is_wt_between_values(word->wi.sep, cn2.curr);
	else
		is_next = is_wt_between_values(word->wi.sep, cn2.next);
	if (is_next && is_curr)
		return (true);
	handle_parser_err(word, is_curr, is_next, can_continue);
	return (false);
}
