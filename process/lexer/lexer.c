/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 07:27:49 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/16 09:20:05 by rkanmado         ###   ########.fr       */
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
	lex->sep.word = ft_substr(sh->line, lex->start, lex->end - lex->start);
	lex->sep.type = is_which_wt(lex->sep.word);
	ft_wunshift(&sh->wsb, set_winfo(lex->sep));
	return ;
}

/* Set word informations */
t_wi	set_winfo(t_sep sep)
{
	t_wi	tw;

	tw.sep = sep.type;
	tw.word = sep.word;
	if (sep.qtype == DQUOTE)
		tw.can_expand = true;
	else
	{
		tw.can_expand = false;
		tw.quote = sep.qtype;
	}
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
	lex.end = 0;
	lex.start = 0;
	while (sh->line[lex.start] != '\0')
	{
		if (is_begin_with_quote(&sh->line[lex.start]) && is_quoted)
			lexing_with_quote(sh, &lex, &quote);
		else
			lexing_without_quote(sh, &lex, &is_quoted);
	}
	return ;
}

void	lexing_with_quote(t_minish *sh, t_lex *lex, t_q *quote)
{
	*quote = is_which_quote(&sh->line[lex->start]);
	lex->start++;
	lex->end = end_quote_delimiter(sh->line, \
				lex, *quote);
	if (lex->is_format_ok == false)
	{
		recursive_rl(sh, lex, ">");
		return ;
	}
	lex->sep.qtype = *quote;
	if (lex->start != lex->end)
		add_new_word(lex, sh);
	lex->start++;
	lex->end++;
	escape_spaces(sh->line, lex);
	return ;
}

void	lexing_without_quote(t_minish *sh, t_lex *lex, t_b *is_quoted)
{
	*is_quoted = 0;
	end_token_delimiter(sh->line, lex);
	lex->sep.qtype = NONE;
	add_new_word(lex, sh);
	escape_spaces(sh->line, lex);
	*is_quoted = 1;
	return ;
}
