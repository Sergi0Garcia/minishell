/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:26:26 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/11 08:16:30 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_heredoc(char *s1)
{
	if (strcmp(s1, "<<") == 0)
		return (1);
	return (0);
}

void	p_interactive_mode(t_minish *sh)
{
	(void) sh;
	return ;
}

void	p_noninteractive_mode(t_minish *sh)
{
	(void) sh;
	return ;
}

void	parse(t_minish *sh)
{
	char	**split;
	int		i;
	char	*concat;

	i = 0;
	concat = NULL;
	split = ft_split(sh->line, ';');
	while (split[i] != NULL)
	{
		if (is_which_wt(split[i]) != NEIN)
		{
			concat = ft_strjoin(concat, split[i]);
			concat = ft_strjoin(concat, " ");
			i++;
		}
	}
}
