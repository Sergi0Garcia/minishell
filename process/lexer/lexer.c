/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 07:27:49 by rkanmado          #+#    #+#             */
/*   Updated: 2022/11/29 12:35:52 by rkanmado         ###   ########.fr       */
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
	printf("can_hspace is the line %s, %d\n", str, next->end);
	while (str[start] && str[start] == ' ')
		start++;
	next->end = start;
	next->word_type = SPACE;
	next->word = " ";
	return (1);
}

t_b	can_switch(char *substr, t_sep *next)
{
	t_wt	wt;

	printf("can_switch is the line %s, %d\n", substr, next->end);
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
		// if (is_sep(str[next.end]) != NEIN)
		// {
			next.end = end_of_sep(str, next.end);
			printf("this is the line %s and the end became %d\n", &str[start], next.end);
			sub = ft_substr(str, start, next.end);
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
		// }
		next.end += 1;;
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
	t_wsb	*wsb;

	wsb = NULL;
	start = 0;
	while (sh->line[start] != '\0')
	{
		sep = next_sep(sh->line, start);
		ft_wunshift(wsb, set_winfo(sep));
		start = sep.end;
		printf("lexing is the line %s, %d\n", sh->line, start);
	}
	return ;
}
