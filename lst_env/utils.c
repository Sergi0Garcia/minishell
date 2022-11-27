/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:14:35 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/27 11:40:29 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_node	*ft_env_last(t_env_node *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_env_node	*ft_env_find(t_env_node *lst, char *str)
{
	while (lst)
	{
		if (is_same_str(lst->name, str))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

int	ft_env_lst_size(t_env_node *lst)
{
	size_t	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
