/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 04:38:09 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/08 07:32:58 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_array(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] && str[i] != NULL)
			free(str[i]);
		i--;
	}
	free(str);
}

int	return_free(char **opts, int st)
{
	int	len;
	int	i;

	i = 0;
	if (!opts || opts == NULL)
		return (st);
	len = c_child(opts);
	while (i < len)
	{
		free(opts[i]);
		i++;
	}
	free(opts);
	return (st);
}

void	free_env_list(t_env **env_lst)
{
	t_env	*tmp;

	while (env_lst && *env_lst)
	{
		tmp = (*env_lst)->next;
		if ((*env_lst)->name && (*env_lst)->name != NULL)
			free((*env_lst)->name);
		if ((*env_lst)->value && (*env_lst)->value != NULL)
			free((*env_lst)->value);
		free((*env_lst));
		*env_lst = tmp;
	}
	*env_lst = NULL;
}
