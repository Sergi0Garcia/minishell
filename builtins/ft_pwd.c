/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:21:50 by segarcia          #+#    #+#             */
/*   Updated: 2022/12/03 22:51:31 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	valid_flag(t_c *cmd)
{
	int		i;
	int		j;
	char	*option;

	if (!cmd || !cmd->opts)
		return (1);
	i = 0;
	while (cmd->opts[i])
	{
		j = 0;
		option = cmd->opts[i];
		while (option[j])
		{
			if (j < 2 && option[j] == '-')
				j++;
			else
			{
				if (option[j] != 'L' && option[j] != 'P')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	handle_error(void)
{
	ft_printf("invalid option\n");
	ft_printf("pwd: usage: pwd [-LP]\n");
	return (EXIT_FAILURE);
}

char	*ft_pwd(t_c *cmd)
{
	char	*res;

	if (!valid_flag(cmd))
	{
		handle_error();
		return (NULL);
	}
	res = getcwd(NULL, PATH_MAX);
	return (res);
}
