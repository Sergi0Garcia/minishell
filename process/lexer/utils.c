/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 07:45:35 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/11 07:59:49 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	remove_spaces(t_minish *sh)
{
	t_w		*word;
	t_wsb	new;

	word = sh->wsb.head;
	init_twsb(&new);
	while (word != NULL)
	{
		if (word->wi.sep != SPACE)
			ft_wunshift(&new, word->wi);
		word = word->next;
	}
	ft_free_stack(&sh->wsb.head, &sh->wsb.head);
	sh->wsb = new;
	return ;
}
