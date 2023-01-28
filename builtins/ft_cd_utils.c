/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 02:35:07 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/28 01:42:32 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	back_flag(char *opt)
{
	int	len;

	len = ft_strlen(opt);
	if (len == 1 && opt[0] == '-')
		return (1);
	return (0);
}

static int	db_back_flag(char *opt)
{
	int	len;

	len = ft_strlen(opt);
	if (len == 2 && opt[0] == '-' && opt[1] == '-')
		return (1);
	return (0);
}

static int	valid_options(char *opt)
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

int	cd_valid_flag(t_c *cmd)
{
	int		i;

	if (!cmd || !cmd ->opts)
		return (1);
	i = 0;
	while (cmd->opts[i])
	{
		if (db_back_flag(cmd->opts[i]))
		{
			if (back_flag(cmd->opts[i + 1]))
				return (2);
			else
				return (1);
		}
		if (back_flag(cmd->opts[i]))
			return (2);
		if (!valid_options(cmd->opts[i]))
			return (0);
		i++;
	}
	return (1);
}

void	cd_handle_error(void)
{
	ft_printf("invalid option");
	ft_printf("\n");
	ft_printf("cd: usage: cd [-L|-P] [dir]");
	ft_printf("\n");
	return ;
}
