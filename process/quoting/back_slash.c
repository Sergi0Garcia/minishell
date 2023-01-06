/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_slash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 09:40:30 by rkanmado          #+#    #+#             */
/*   Updated: 2022/12/10 15:37:44 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

typedef enum s_backslash
{
	t_b quoted;
	t_b exist;
}	t_slash;

t_slash	is_backslash(char *str)
{
	t_slash	slash;
	int		i;

	slash.exist = false;
	slash.quoted = false;
	while (*str)
	{
		if (*str == '\\')
			slash.exist = true;
	}
	return (slash);
}

void	quoting(t_sep *ws)
{
	t_slash	slash;

	slash = is_backslash(ws->word);
	if (slash.exist)
	{
		if (slash.quoted)
		{

		}
	}
}
