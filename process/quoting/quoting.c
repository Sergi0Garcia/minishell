/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 22:03:31 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/06 03:33:57 by rkanmado         ###   ########.fr       */
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
		return (-1);
}

t_b	is_begin_with_quote(char *str)
{
	if (*str == '\'' || *str == '\"')
		return (true);
	else
		return (false);
}

/* Check if the string contains quotes */
t_b	contain_quote(char *str)
{
	while (*str)
	{
		if (*str == '\'')
			return (true);
		else if (*str == '\"')
			return (true);
	}
	return (false);
}

int	end_quote_delimiter(char *str, int i, t_q qtype)
{
	int	end;

	end = i;
	if (qtype == DQUOTE)
	{
		while (str[end] != '\"')
			end++;
	}
	else if (qtype == SQUOTE)
	{
		while (str[end] != '\'')
			end++;
	}
	else
		return (-1);
	return (end - i);
}
