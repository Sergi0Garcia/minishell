/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:21:50 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/17 02:32:07 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	vaild_option(char *opt)
{
	int	i;

	i = 0;
	while (opt[i])
	{
		if (i < 2 && opt[i] == '-')
			i++;
		else
		{
			if (opt[i] != 'L' && opt[i] != 'P')
				return (0);
		}
		i++;
	}
	return (1);
}

static int	valid_flag(t_c *cmd)
{
	int		i;
	char	*option;

	if (!cmd || !cmd->opts)
		return (1);
	i = 0;
	while (cmd->opts[i])
	{
		option = cmd->opts[i];
		if (!vaild_option(option))
			return (0);
		i++;
	}
	return (1);
}

static int	handle_error(void)
{
	ft_printf("invalid option");
	ft_printf("\n");
	ft_printf("pwd: usage: pwd [-LP]");
	ft_printf("\n");
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
	ft_printf("%s\n", res);
	return (res);
}
