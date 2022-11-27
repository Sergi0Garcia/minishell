/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:59:06 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/27 17:13:22 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int valid_flag(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(char **opt, char **arg)
{
	int nl_req;
	int	i;

	nl_req = 1;
	if (opt[0] && ft_strlen(opt[0]) > 1
		&& opt[0][0] == '-'
		&& opt[0][1] == 'n'
		&& valid_flag(opt[0]) == 1)
			nl_req = 0;
	i = 0;
	while (arg[i])
	{
		ft_printf("%s", arg[i]);
		if (arg[i + 1])
			ft_printf(" ");
		i++;
	}
	if (nl_req)
		ft_printf("\n");
}