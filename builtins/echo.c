/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:59:06 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/27 11:31:08 by segarcia         ###   ########.fr       */
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

void	ft_echo(char **arg)
{
	int nl_req;
	int	i;

	i = 0;
	nl_req = 1;
	if (ft_strlen(arg[0]) > 1 && arg[0][0] == '-' && arg[0][1] == 'n')
		if (valid_flag(arg[0]) == 1)
			nl_req = 0;
	if (!nl_req)
		i++;
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1])
			printf(" ");
		i++;
	}
	if (nl_req)
		printf("\n");
}