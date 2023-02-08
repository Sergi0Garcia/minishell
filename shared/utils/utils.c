/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:45:57 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/07 03:53:30 by rkanmado         ###   ########.fr       */
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

char	*str_joinsh(char **arg_or_opt, char *str)
{
	char	*tmp;

	tmp = *arg_or_opt;
	*arg_or_opt = ft_strjoin(tmp, str);
	free(tmp);
	return (*arg_or_opt);
}

t_b	is_sep_type(t_wt wt)
{
	if (wt == WORD || wt == DLESS || wt == LESS || wt == GREAT \
		|| wt == DGREAT || wt == SPACES || wt == PIPE)
		return (true);
	return (false);
}

char	*char_of_sep(t_wt wt)
{
	if (wt == PIPE)
		return ("|");
	else if (wt == GREAT)
		return (">");
	else if (wt == DGREAT)
		return (">>");
	else if (wt == SPACES)
		return (" ");
	else if (wt == LESS)
		return ("<");
	else if (wt == DLESS)
		return ("<<");
	else if (wt == ANDIF)
		return ("&");
	else
		return (" ");
}

t_wt	is_sep(char s1)
{
	if (s1 == '|')
		return (PIPE);
	else if (s1 == '>')
		return (GREAT);
	else if (s1 == '<')
		return (LESS);
	else if (s1 == '&')
		return (ANDIF);
	else if (s1 == ' ')
		return (SPACES);
	else
		return (WORD);
}
