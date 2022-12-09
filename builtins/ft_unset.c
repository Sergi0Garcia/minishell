/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:55:56 by segarcia          #+#    #+#             */
/*   Updated: 2022/12/09 11:14:49 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_unset(t_c *cmd, t_env_node **env_lst)
{
	int	i;

	i = 0;
	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	while (cmd->args[i])
	{
		unset_env(env_lst, cmd->args[i]);
		i++;
	}
}
