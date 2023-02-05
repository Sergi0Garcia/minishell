/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:41:50 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/05 10:45:13 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

static int	str_numeric(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		if (str[i] == '-' && str[i + 1]
			&& str[i + 1] >= '0' && str[i + 1] <= '9')
			return (1);
		else if (str[i] == '+' && i == 0)
			i++;
		else if (str[i] == '+' && i > 0)
			return (2);
		else if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (2);
	}
	return (0);
}

static int	return_exit(int status, int err, t_minish *sh)
{
	if (sh && sh != NULL)
	{
		free_all(sh, 5);
		//system("leaks minishell");
	}
	if (status != -1)
		ft_printf("exit\n");
	if (err != -1)
		ci_error(err, status);
	exit(status);
}

int	ft_exit(t_ci cmd, t_minish *sh)
{
	int		res;
	char	**c_args;

	if (!cmd.opts && !ft_strlen(cmd.opts)
		&& !cmd.args && !ft_strlen(cmd.args))
		return (return_exit(0, -1, sh));
	if (cmd.opts && ft_strlen(cmd.opts))
	{
		if (str_numeric(cmd.opts) == 1)
			return (return_exit(1, -1, sh));
		return (return_exit(255, ERR_NUM_ARG, sh));
	}
	if (cmd.args && ft_strlen(cmd.args))
	{
		c_args = ft_split(cmd.args, ' ');
		if (c_args && c_child(c_args) > 1)
			return (ci_error(ERR_EXIT_MARG, 1));
		res = str_numeric(c_args[0]);
		if (res == 2)
			return (return_exit(255, ERR_NUM_ARG, sh));
		if (res == 1)
			return (return_exit(255, -1, sh));
		return (return_exit(ft_atoi(c_args[0]) % 256, -1, sh));
	}
	return (return_exit(0, -1, sh));
}
