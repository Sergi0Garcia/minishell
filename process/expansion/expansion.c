/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 05:10:54 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/22 05:16:20 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expansion(t_minish *sh)
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
	start = 0;
	while (tmp[start] != '\0')
	{
		if (tmp[start] == '$')
		{
			if (can_apply_expansion(str))
				expand_var(str, start);
		}
		start++;
	}
	return ;
}

void	expand_var(char **str, size_t start)
{
	char	*tmp;
	size_t	end;
	char	*env_value;
	t_lex	lex;

	end = 0;
	tmp = *str;
	end_of_expandation(&tmp[start], &end);
	lex.start = start;
	lex.end = end;
	env_value = retrieve_env(tmp + 1);
	replace_str(str, env_value, &lex);
	return ;
}

void	end_of_expandation(char *str, size_t *end)
{
	while (str != NULL)
	{
		if ((*str == '\0' || *str == ' ' || *str == '\"'))
			break ;
		str++;
		*end += 1;
	}
	return ;
}
