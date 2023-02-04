/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 21:34:43 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/04 21:49:28 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_single_cmd(t_c *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	if (i == 1)
		return (1);
	else
		return (0);
}

int	is_single_execution(t_c *cmd)
{
	if (is_single_cmd(cmd)
		&& (is_same_str(cmd->ci.name, "exit")
			|| is_same_str(cmd->ci.name, "export")
			|| is_same_str(cmd->ci.name, "unset")
			|| is_same_str(cmd->ci.name, "cd")))
		return (1);
	return (0);
}
