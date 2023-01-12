/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 07:45:35 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/12 22:59:37 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	remove_spaces(t_minish *sh)
{
	t_w		*word;
	t_wsb	new;

	word = sh->wsb.head;
	init_twsb(&new);
	while (word != NULL)
	{
		if (word->wi.sep != SPACE)
			ft_wunshift(&new, word->wi);
		word = word->next;
	}
	ft_free_stack(&sh->wsb.head, &sh->wsb.head);
	sh->wsb = new;
	return ;
}

void	check_greatorless(t_wt *last, char *str)
{
	t_wt	curr;

	if (*(str + 1) && (last == LESS || last == GREAT))
	{
		curr = is_sep(*(str + 1));
		if (curr == last)
			*last = is_which_wt(ft_substr(str, 0, 2));
	}
	return ;
}
