/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:59:06 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/29 17:51:45 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	valid_flag(t_ci cmd)
{
	int	len;

	if (!cmd.opts)
		return (0);
	len = ft_strlen(cmd.opts);
	if (!len)
		return (0);
	if (len != 2)
		return (0);
	if (cmd.opts[0] == '-' && cmd.opts[1] == 'n')
		return (1);
	return (0);
}

static void	print_words(t_ci cmd, int new_line)
{
	int	i;

	i = 0;
	if (cmd.opts && new_line)
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

void	ft_echo(t_ci cmd)
{
	int		new_line;

	new_line = !valid_flag(cmd);
	print_words(cmd, new_line);
}
