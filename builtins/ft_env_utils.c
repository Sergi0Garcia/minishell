/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:22:12 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/17 02:44:49 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exists_env(t_env_node **env_lst, char *str)
{
	int			found;
	t_env_node	*tmp;

	found = 0;
	tmp = *env_lst;
	while (tmp)
	{
		if (is_same_str(tmp->name, str))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*env_value(t_env_node **env_lst, char *name)
{
	t_env_node	*tmp;

	tmp = *env_lst;
	if (exists_env(env_lst, name))
	{
		while (tmp)
		{
			if (is_same_str(tmp->name, name))
				return (tmp->value);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

void	print_env(t_env_node **env_lst, int with_declare)
{
	t_env_node	*tmp;

	tmp = *env_lst;
	while (tmp)
	{
		if (with_declare)
		{
			ft_printf("declare -x ");
			ft_printf("%s", tmp->name);
			if (tmp->value)
			{
				ft_printf("=\"%s\"\n", tmp->value);
			}
			else
				ft_printf("\n");
		}
		else
		{
			if (tmp->value)
				ft_printf("%s=%s\n", tmp->name, tmp->value);
		}
		tmp = tmp->next;
	}
}
