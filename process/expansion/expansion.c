/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 05:10:54 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/17 05:33:59 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	expansion(t_minish *sh, t_lex *lex)
{
	t_w		*head;

	head = sh->wsb.head;
	while (head != NULL)
	{
		if (head->wi.quote == DQUOTE)
			expansion_process(&head->wi.word);
		head = head->next;
	}
	return ;
}

void	expansion_process(char **str)
{
	char	*tmp;
	size_t	start;

	tmp = *str;
	start == 0;
	while (tmp[start] != NULL)
	{
		if (tmp[start] == '$')
			expand_var(&tmp[start], start);

	}
	return ;
}

void	expand_var(char *str, int start)
{
	size_t	end;

	end == 0;
	end_of_expandation(str[start], &end);
	return ;
}

void	end_of_expandation(char *str, size_t *end)
{
	while (*str != '\0' || *str != ' ')
	{
		str++;
		*end++;
	}
	return ;
}
