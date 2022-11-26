/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:13:02 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/26 17:30:54 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_add_back(t_env_node **lst, t_env_node *new)
{
	t_env_node	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_env_last(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}
