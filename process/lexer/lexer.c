/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 07:27:49 by rkanmado          #+#    #+#             */
/*   Updated: 2022/11/30 13:53:39 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* This function check many how spaces you have and consider it as one
 * Imagine you have something like that
 * echo       "Hello World"
 * this command should become
 * echo "Hello Word"
 */

typedef struct s_lexing
{
	int			start;
	int			end;
	t_wt		last;
	t_wt		new;
	t_sep		sep;
}	t_lex;

static void	increment(t_lex *lex, t_minish *sh)
{
	lex->sep.type = lex->last;
	lex->sep.word = ft_substr(sh->line, lex->start, lex->end - lex->start);
	ft_wunshift(&sh->wsb, set_winfo(lex->sep));
	lex->start = lex->end;
	lex->last = lex->new;
	return ;
}

t_wi	set_winfo(t_sep sep)
{
	t_wi	tw;

	tw.sep = sep.type;
	tw.word = sep.word;
	return (tw);
}

void	lexing(t_minish *sh)
{
	t_lex	lex;

	init_twsb(&sh->wsb);
	lex.last = is_sep(sh->line[0]);
	lex.end = 0;
	lex.start = 0;
	while (sh->line[lex.end] != '\0')
	{
		lex.new = is_sep(sh->line[lex.end]);
		if (lex.new != lex.last)
			increment(&lex, sh);
		else
			lex.end++;
	}
	if (lex.start != lex.end)
		increment(&lex, sh);
	return ;
}
