/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 08:02:46 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/08 03:49:58 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_status;

void	parser_error(char *str)
{
	g_status = 258;
	printf("minishell: syntax error near unexpected token `%s'\n", str);
	return ;
}

void	handle_parser_err(t_w *word, t_b is_curr, t_b is_next, \
		t_b *can_continue)
{
	*can_continue = false;
	if (!is_next)
		parser_error(char_of_sep(word->next->wi.sep));
	else if (!is_curr)
		parser_error(char_of_sep(word->wi.sep));
	return ;
}
