/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:26:26 by rkanmado          #+#    #+#             */
/*   Updated: 2022/11/26 14:23:58 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_sep(char *s1)
{
	if (strcmp(s1, "|") == 0)
		return (1);
	else if (strcmp(s1, ">") == 0)
		return (2);
	else if (strcmp(s1, ">>") == 0)
		return (3);
	else if (strcmp(s1, "<") == 0)
		return (4);
	else if (strcmp(s1, "<<") == 0)
		return (5);
	else
		return (0);
}

int	is_heredoc(char *s1)
{
	if (strcmp(s1, "<<") == 0)
		return (1);
	return (0);
}

void	parse(t_minish *sh)
{
	char	**split;
	int		i;
	char	*concat;

	i = 0;
	concat = NULL;
	split = ft_split(sh->line, ' ');
	while (split[i] != NULL)
	{
		if (is_sep(split[i]) != 0)
		{
			concat = ft_strjoin(concat, split[i]);
			concat = ft_strjoin(concat, " ");
			i++;
		}
	}
}
