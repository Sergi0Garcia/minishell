/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:55:56 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/01 04:57:34 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	ft_unset(t_ci cmd, t_env **env_lst)
{
	int		i;
	char	**args;

	i = 0;
	args = ft_split(cmd.args, ' ');
	if (!args || !args[0])
		return (EXIT_SUCCESS);
	while (args[i])
	{
		unset_env(env_lst, args[i]);
		i++;
	}
	free_array(args);
	return (EXIT_SUCCESS);
}
