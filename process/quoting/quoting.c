/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 22:03:31 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/16 09:09:22 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_q	is_which_quote(char *str)
{
	if (*str == '\'')
		return (SQUOTE);
	else if (*str == '\"')
		return (DQUOTE);
	else
		return (NONE);
}

t_b	is_begin_with_quote(char *str)
{
	if (*str == '\'' || *str == '\"')
		return (true);
	else
		return (false);
}

/* Read recursively the line until the format is ok
* if the new line was readed we have to set start index
* and the end index to zero
*/
void	recursive_rl(t_minish *sh, t_lex *lex, char *title)
{
	char	*str;

	str = readline(title);
	str = ft_strjoin(str, "\n");
	sh->line = ft_strjoin(sh->line, str);
	lex->end = 0;
	lex->start = 0;
	lex->is_format_ok = true;
	ft_free_stack(&sh->wsb.head, &sh->wsb.tail);
	init_twsb(&sh->wsb);
	return ;
}

int	end_quote_delimiter(char *str, t_lex *lex, t_q qtype)
{
	int	end;

	end = lex->start;
	lex->is_format_ok = false;
	if (qtype == DQUOTE)
	{
		while (str[end] != '\0')
		{
			if (str[end] == '\"')
				lex->is_format_ok = true;
			end++;
		}
	}
	else if (qtype == SQUOTE)
	{
		while (str[end] != '\0')
		{
			if (str[end] == '\'')
				lex->is_format_ok = true;
			end++;
		}
	}
	else
		return (-1);
	return (end);
}
