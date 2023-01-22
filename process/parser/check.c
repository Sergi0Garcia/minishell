/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:57:01 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/22 05:22:13 by rkanmado         ###   ########.fr       */
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
		return (SPACE);
	else if (strcmp(s1, "<") == 0)
		return (LESS);
	else if (strcmp(s1, "<<") == 0)
		return (LESS);
	else if (strcmp(s1, "&") == 0)
		return (ANDIF);
	else if (strcmp(s1, "||") == 0)
		return (ORIF);
	else
		return (WORD);
}
