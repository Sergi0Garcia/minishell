/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:25:31 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/01 04:53:55 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_export(t_ci cmd, t_env **env_lst)
{
	int		i;
	char	**args;

	i = 0;
	args = ft_split(cmd.args, ' ');
	if (!args || !args[0])
	{
		print_env(env_lst, 1);
		return (EXIT_SUCCESS);
	}
	while (args[i])
	{
		new_env(env_lst, args[i]);
		i++;
	}
	free_array(args);
	return (EXIT_SUCCESS);
}
