/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 22:03:31 by rkanmado          #+#    #+#             */
/*   Updated: 2022/12/07 22:54:39 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	is_quote(char *str)
{
	if (*str == '\'')
		return (1);
	else if (*str == '\"')
		return (2);
	else
		return (0);
}

void	end_quote(char *str, int type, t_minish *sh)
{
	if (str == "\'")
		endquote(str, sh);
	else if (str == "\"")
		enddquote(str, sh);
	else
		return ;
}

void	endquote(char *str, t_minish *sh)
{
	int	quote;
	int	dquote;

	quote = 0;
	dquote = 0;
	while (*str)
	{
		if (*str == '\'')
			quote++;
		else if (*str == '\"')
			dquote++;
	}
	return ;
}
