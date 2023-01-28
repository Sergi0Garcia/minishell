/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:36:25 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/28 00:18:50 by rkanmado         ###   ########.fr       */
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
	}
	return (false);
}

int	get_fd(void)
{
	return (1);
}