/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:45:57 by rkanmado          #+#    #+#             */
/*   Updated: 2022/11/29 10:17:35 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	end_of_sep(char *str, int start)
{
	while (is_sep(str[start]) != NEIN)
		start++;
	return (start);
}

t_b	is_sep_type(t_wt wt)
{
	if (wt == WORD || wt == DIREDIRECT || wt == SIREDIRECT || wt == SOREDIRECT \
		|| wt == DOREDIRECT || wt == SPACE || wt == PIPE)
		return (true);
	return (false);
}

t_wt	is_which_sep(char *s1)
{
	if (strcmp(s1, "|") == 0)
		return (PIPE);
	else if (strcmp(s1, ">") == 0)
		return (SOREDIRECT);
	else if (strcmp(s1, ">>") == 0)
		return (DOREDIRECT);
	else if (strcmp(s1, " ") == 0)
		return (SPACE);
	else if (strcmp(s1, "<") == 0)
		return (SIREDIRECT);
	else if (strcmp(s1, "<<") == 0)
		return (DIREDIRECT);
	else if (strcmp(s1, "&") == 0)
		return (AND);
	else
		return (NEIN);
}

t_wt	is_sep(char s1)
{
	if (s1 == '|')
		return (PIPE);
	else if (s1 == '>')
		return (SOREDIRECT);
	else if (s1 == '<')
		return (SIREDIRECT);
	else if (s1 == ' ')
		return (SPACE);
	else
		return (-1);
}
