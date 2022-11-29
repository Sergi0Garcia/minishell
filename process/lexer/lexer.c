/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 07:27:49 by rkanmado          #+#    #+#             */
/*   Updated: 2022/11/30 00:25:57 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* This function check many how spaces you have and consider it as one
 * Imagine you have something like that
 * echo       "Hello World"
 * this command should become
 * echo "Hello Word"
 */

t_b	can_hspace(int start, char *str, t_sep *next)
{
	int	index;

	index = start;
	while (str[index] && str[index] == ' ')
		index++;
	if (index > start)
	{
		next->end = index;
		next->word_type = SPACE;
		next->word = " ";
	}
	return (1);
}

t_b	can_switch(char *substr, t_sep *next)
{
	t_wt	wt;

	wt = is_which_sep(substr);
	if (wt != NEIN)
	{
		next->word = substr;
		next->word_type = wt;
		return (true);
	}
	return (false);
}

t_sep	next_sep(char *str, int start)
{
	t_sep	next;
	char	*sub;

	next.end = start;
	while (str[next.end])
	{
		next.end = end_of_sep(str, next.end);
		if (next.end - start == 0)
			sub = ft_substr(str, start, 1);
		else
			sub = ft_substr(str, start, next.end - start);
		next.word_type = is_which_sep(sub);
		if (can_hspace(start, str, &next))
			return (next);
		else if (can_switch(sub, &next))
			return (next);
		else
		{
			next.word = sub;
			next.word_type = WORD;
			return (next);
		}
		next.end += 1;
	}
	return (next);
}

t_wi	set_winfo(t_sep sep)
{
	t_wi	tw;

	tw.sep = sep.word_type;
	tw.word = sep.word;
	return (tw);
}

void	lexing(t_minish *sh)
{
	int		start;
	t_sep	sep;

	init_twsb(&sh->wsb);
	start = 0;
	while (sh->line[start] != '\0')
	{
		sep = next_sep(sh->line, start);
		ft_wunshift(&sh->wsb, set_winfo(sep));
		start = sep.end;
		printf("lexing is the line %s, %d\n", sh->line, start);
	}
	return ;
}
