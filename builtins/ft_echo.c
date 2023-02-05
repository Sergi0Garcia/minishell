/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:59:06 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/05 12:12:56 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	valid_flag(char *str)
{
	int	i;
	int	len;

	if (!str || !ft_strlen(str))
		return (0);
	len = ft_strlen(str);
	if (len < 2)
		return (0);
	if (str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (i < len)
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	needs_new_line(int i)
{
	if (i > 0)
		return (0);
	else
		return (1);
}

static void	print_c_opts(int i, int len, char **opts)
{
	while (i < len)
	{
		ft_printf("%s", opts[i]);
		if (opts[i + 1])
			ft_printf(" ");
		i++;
	}
}

static int	print_opts(char *str, char *args)
{
	char	**opts;
	int		opts_len;
	int		flag;
	int		i;
	int		j;

	i = 0;
	flag = 0;
	opts = ft_split(str, ' ');
	opts_len = c_child(opts);
	while (opts[i] && flag == 0)
	{
		flag = !valid_flag(opts[i]);
		if (flag == 0)
			i++;
	}
	j = i;
	flag = needs_new_line(i);
	print_c_opts(i, opts_len, opts);
	if ((j != opts_len) && (args && ft_strlen(args)))
		ft_printf(" ");
	return_free(opts, 0);
	return (flag);
}

int	ft_echo(t_ci cmd)
{
	int	new_line;

	new_line = print_opts(cmd.opts, cmd.args);
	if (cmd.args && ft_strlen(cmd.args))
		ft_printf("%s", cmd.args);
	if (new_line)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}
