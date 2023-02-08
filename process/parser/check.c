/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:57:01 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/08 01:44:19 by rkanmado         ###   ########.fr       */
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
	if (s1[0] == '|')
		return (PIPE);
	else if (s1[0] == '>' && s1[1] != '\0' && s1[1] == '>')
		return (DGREAT);
	else if (s1[0] == '>')
		return (GREAT);
	else if (s1[0] == ' ')
		return (SPACES);
	else if (s1[0] == '<' && s1[1] != '\0' && s1[1] == '<')
		return (DLESS);
	else if (s1[0] == '<')
		return (LESS);
	else if (s1[0] == '&')
		return (ANDIF);
	else if (s1[0] == '|' && s1[1] != '\0' && s1[1] == '|')
		return (ORIF);
	else
		return (WORD);
}

t_b	can_delimitate(char *s1, t_wt last, size_t *end)
{
	if (s1[*end] == '|' && last != is_which_wt(&s1[*end]))
		return (true);
	else if (s1[*end] == '>' && s1[*end + 1] != '\0' && s1[*end + 1] == '>' \
		&& last != is_which_wt(&s1[*end]))
		return (true);
	else if (s1[*end] == '>' && last != is_which_wt(&s1[*end]))
		return (true);
	else if (s1[*end] == ' ' && last != is_which_wt(&s1[*end]))
		return (true);
	else if (s1[*end] == '<' && s1[*end + 1] != '\0' && s1[*end + 1] == '<' \
		&& last != is_which_wt(&s1[*end]))
		return (true);
	else if (s1[*end] == '<' && last != is_which_wt(&s1[*end]))
		return (true);
	else if (s1[*end] == '&' && last != is_which_wt(&s1[*end]))
		return (true);
	else if (s1[*end] == '|' && s1[*end + 1] != '\0' && s1[*end + 1] == '|' \
		&& last != is_which_wt(&s1[*end]))
		return (true);
	else if (last != is_which_wt(&s1[*end]))
		return (true);
	else
		return (false);
}

void	inc_lex(char *s1, size_t *end)
{
	if (strcmp(s1, "|") == 0)
		*end += 1;
	else if (s1[*end] == '>' && s1[*end + 1] != '\0' && s1[*end + 1] == '>')
		*end += 2;
	else if (strcmp(s1, ">") == 0)
		*end += 1;
	else if (strcmp(s1, " ") == 0)
		*end += 1;
	else if (s1[*end] == '<' && s1[*end + 1] != '\0' && s1[*end + 1] == '<')
		*end += 2;
	else if (strcmp(s1, "<") == 0)
		*end += 1;
	else if (strcmp(s1, "&") == 0)
		*end += 1;
	else if (strcmp(s1, "||") == 0)
		*end += 2;
	else
		*end += 1;
	return ;
}

t_cn	set_wt_values(t_wt *curr, t_wt *next, t_cn *cn)
{
	cn->curr = curr;
	cn->next = next;
	return (*cn);
}
