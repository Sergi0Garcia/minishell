/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:59:06 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/01 14:02:42 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	valid_flag_n(char *str, int i)
{
	if (str[i] == ' '
		&& str[i + 1] && str[i + 1] == '-'
		&& str[i + 2] && str[i + 2] == 'n')
		return (1);
	return (0);
}

static int	valid_flag(t_ci cmd)
{
	int	len;
	int	i;

	if (!cmd.opts)
		return (0);
	len = ft_strlen(cmd.opts);
	if (!len || len < 2)
		return (0);
	if (cmd.opts[0] != '-')
		return (0);
	if (cmd.opts[1] != 'n')
		return (0);
	i = 2;
	while (i < len)
	{
		if (cmd.opts[i] != 'n')
		{
			if (!valid_flag_n(cmd.opts, i))
				return (0);
			i++;
		}
		i++;
	}
	return (1);
}

static void	print_words(t_ci cmd, int new_line)
{
	int	i;

	i = 0;
	if (cmd.opts && ft_strlen(cmd.opts) && new_line)
	{
		ft_printf("%s", cmd.opts);
		if (cmd.args)
			ft_printf(" ");
	}
	if (cmd.args)
		ft_printf("%s", cmd.args);
	if (new_line)
		ft_printf("\n");
}

int	ft_echo(t_ci cmd)
{
	int		new_line;

	new_line = !valid_flag(cmd);
	print_words(cmd, new_line);
	return (EXIT_SUCCESS);
}
