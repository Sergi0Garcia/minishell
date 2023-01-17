/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:25:31 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/17 02:38:24 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_export(t_c *cmd, t_env_node **env_lst)
{
	int	i;

	i = 0;
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		print_env(env_lst, 1);
		return ;
	}
	while (cmd->args[i])
	{
		new_env(env_lst, cmd->args[i]);
		i++;
	}
}
