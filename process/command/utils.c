/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:36:25 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/09 05:36:59 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Function to check if an argument is an option */

t_b	is_option(char *str)
{
	if (*str == '-')
		return (true);
	return (false);
}

t_b	is_opt_already_exits(t_wsb *wsb, char *opt)
{
	t_w	*token;

	token = wsb->head;
	while (token != NULL)
	{
		if (is_same_str(token->wi.word, opt))
			return (true);
		token = token->next;
	}
	return (false);
}

char	*add_arg_or_opt(char **arg_or_opt, t_wi wi)
{
	char	*tmp;
	char	*space;

	tmp = *arg_or_opt;
	space = " ";
	if (ft_strlen(tmp) > 0)
	{
		*arg_or_opt = ft_strjoin(tmp, space);
		free(tmp);
	}
	tmp = str_joinsh(arg_or_opt, wi.word);
	return (tmp);
}

t_b	can_increment_word(t_w **word)
{
	if ((*word)->next == NULL)
	{
		parser_error("newline");
		return (false);
	}
	*word = (*word)->next;
	return (true);
}

t_b	handle_redirect(t_w **head, int *infile)
{
	t_w	*tmp;
	int	i;

	tmp = *head;
	i = 0;
	if (!can_increment_word(head))
		return (false);
	*infile = get_fd(tmp->next->wi.word, tmp->wi.sep, &i);
	if (i == -1)
		return (false);
	return (true);
}
