/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 07:27:49 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/11 07:54:33 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* This function check many how spaces you have and consider it as one
 * Imagine you have something like that
 * echo       "Hello World"
 * this command should become
 * echo "Hello Word"
 */

/* Adding new data into the stack */
void	add_new_word(t_lex *lex, t_minish *sh)
{
	lex->sep.type = lex->last;
	lex->sep.word = ft_substr(sh->line, lex->start, lex->end - lex->start);
	ft_wunshift(&sh->wsb, set_winfo(lex->sep));
	lex->start = lex->end;
	lex->last = lex->new;
	return ;
}

/* Set word informations */
t_wi	set_winfo(t_sep sep)
{
	t_wi	tw;

	tw.sep = sep.type;
	tw.word = sep.word;
	return (tw);
}

/* separate string by word */
void	lexing(t_minish *sh)
{
	t_lex	lex;
	t_q		quote;
	t_b		is_quoted;

	init_twsb(&sh->wsb);
	quote = NONE;
	is_quoted = 1;
	lex.last = is_sep(sh->line[0]);
	lex.end = 0;
	lex.start = 0;
	while (sh->line[lex.end] != '\0')
	{
		if (is_begin_with_quote(&sh->line[lex.start]) && is_quoted)
			lexing_with_quote(sh, &lex, &quote);
		else
			lexing_without_quote(sh, &lex, &is_quoted);
	}
	if (lex.start != lex.end)
		add_new_word(&lex, sh);
	remove_spaces(sh);
	return ;
}

void	lexing_with_quote(t_minish *sh, t_lex *lex, t_q *quote)
{
	*quote = is_which_quote(&sh->line[lex->start]);
	lex->end = end_quote_delimiter(&sh->line[lex->start], \
				lex->start, *quote);
	if (lex->new != lex->last)
		add_new_word(lex, sh);
	return ;
}

void	lexing_without_quote(t_minish *sh, t_lex *lex, t_b *is_quoted)
{
	*is_quoted = 0;
	lex->new = is_sep(sh->line[lex->end]);
	if (lex->new != lex->last)
	{
		add_new_word(lex, sh);
		*is_quoted = 1;
	}
	else
		lex->end++;
	return ;
}
