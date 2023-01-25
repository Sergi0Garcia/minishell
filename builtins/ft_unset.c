/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:55:56 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/25 03:15:31 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_unset(t_c *cmd, t_env_node **env_lst)
{
	int		i;
	char	**args;

	args = ft_split(cmd->ci.args, ' ');

	i = 0;
	if (!cmd || !args || !args[0])
		return ;
	while (args[i])
	{
		unset_env(env_lst, args[i]);
		i++;
	}
}
