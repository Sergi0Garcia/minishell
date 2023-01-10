/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 00:50:29 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/10 06:49:26 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parser(t_minish *sh)
{
	int		i;
	t_w		*word;
	t_kvp	*kvp;

	i = 0;
	kvp = get_kv_pairs();
	word = sh->wsb.head;
	while (word != NULL)
	{
		if (i == 0)
			is_edges_good(word, kvp, 1);
		else if (i == sh->wsb.size - 1)
			is_edges_good(word, kvp, 0);
		else
			is_between_good(word, kvp);
	}
}

t_b	is_edges_good(t_w *word, t_kvp *kvp, int begin)
{
	t_b		is_curr_exist;
	t_b		is_next_exist;
	t_cn	cn;

	cn = get_according_values(word->wi.sep);
	is_curr_exist = is_wt_between_values(word->wi.sep, cn.curr);
	is_next_exist = is_wt_between_values(word->next->wi.sep, cn.next);
	if (is_curr_exist && begin)
		return (true);
	else if (is_next_exist && !begin)
		return (true);
	else
		return (false);
}

t_b	is_between_good(t_w *word, t_kvp *kvp)
{
	t_b		is_curr_exist;
	t_b		is_next_exist;
	t_cn	cn;

	cn = get_according_values(word->wi.sep);
	is_curr_exist = is_wt_between_values(word->wi.sep, cn.curr);
	is_next_exist = is_wt_between_values(word->next->wi.sep, cn.next);
	if (is_curr_exist && is_next_exist)
		return (true);
	else
		return (false);
}
