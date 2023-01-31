/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:57:01 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/30 01:45:54 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_b	is_wt_between_values(t_wt word_type, t_wt *list)
{
	int	i;

	i = 0;
	if (list == NULL)
		return (false);
	while (list[i])
	{
		if (!list[i])
			break ;
		if (word_type == list[i])
			return (true);
		i++;
	}
	return (false);
}

t_wt	is_which_wt(char *s1)
{
	if (strcmp(s1, "|") == 0)
		return (PIPE);
	else if (strcmp(s1, ">") == 0)
		return (GREAT);
	else if (strcmp(s1, ">>") == 0)
		return (DGREAT);
	else if (strcmp(s1, " ") == 0)
		return (SPACES);
	else if (strcmp(s1, "<") == 0)
		return (LESS);
	else if (strcmp(s1, "<<") == 0)
		return (DLESS);
	else if (strcmp(s1, "&") == 0)
		return (ANDIF);
	else if (strcmp(s1, "||") == 0)
		return (ORIF);
	else
		return (WORD);
}

t_cn	set_wt_values(t_wt *curr, t_wt *next, t_cn *cn)
{
	cn->curr = curr;
	cn->next = next;
	return (*cn);
}
