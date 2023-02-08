/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 05:10:54 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/08 07:02:00 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expansion(t_minish *sh)
{
	t_w		*head;

	head = sh->wsb.head;
	while (head != NULL)
	{
		if (head->wi.quote == DQUOTE || head->wi.quote == NONE)
			expansion_process(&head->wi.word, sh->env_lst);
		head = head->next;
	}
	return ;
}

void	expansion_process(char **str, t_env *env_lst)
{
	char	*tmp;
	size_t	start;

	tmp = *str;
	start = 0;
	while (tmp[start] != '\0')
	{
		if (tmp[start] == '$')
		{
			if (!tmp[start + 1])
				break ;
			if (can_apply_expansion(str))
				expand_var(str, &start, env_lst);
			tmp = *str;
			start = 0;
			continue ;
		}
		start++;
	}
	return ;
}

void	expand_var(char **str, size_t *start, t_env *env_lst)
{
	char	*tmp;
	size_t	end;
	char	*env_val;
	t_lex	lex;

	end = 0;
	tmp = *str;
	end_of_expansion(&tmp[*start], &end);
	lex.start = *start;
	lex.end = end;
	tmp = ft_substr(tmp, *start + 1, end);
	env_val = env_value(&env_lst, tmp);
	free(tmp);
	replace_str(str, env_val, &lex);
	free(env_val);
	*start = lex.start;
	return ;
}

void	end_of_expansion(char *str, size_t *end)
{
	int	i;

	i = 0;
	++str;
	while (str != NULL)
	{
		if (i == 0 && *str == '$')
		{
			*end += 1;
			break ;
		}
		i++;
		if (*str == '\0' || *str == ' ' || *str == '\"' \
			|| *str == '$')
			break ;
		str++;
		*end += 1;
	}
	return ;
}
