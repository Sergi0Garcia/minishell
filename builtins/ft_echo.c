/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:59:06 by segarcia          #+#    #+#             */
/*   Updated: 2022/12/04 00:48:00 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	valid_flag(t_c *cmd)
{
	int		i;

	if (!cmd->opts || !cmd->opts[0])
		return (0);
	if (cmd->opts[0][0] != '-')
		return (0);
	if (cmd->opts[0][1] != 'n')
		return (0);
	i = 2;
	while (cmd->opts[0][i])
	{
		if (cmd->opts[0][i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	print_words(char **str, int start)
{
	int	i;

	i = start;
	while (str && str[i])
	{
		ft_printf("%s", str[i]);
		if (str[i + 1])
			ft_printf(" ");
		i++;
	}
}

static void	print_nl(int nl_req)
{
	if (nl_req)
		ft_printf("\n");
}

static void	handle_space(t_c *cmd, int nl_req)
{
	int	args_len;
	int	opts_len;
	int i;

	i = -1;
	while (cmd->args && cmd->args[++i]);
	args_len = i;
	i = -1;
	while (cmd->opts && cmd->opts[++i]);
	opts_len = i - !nl_req;
	if (opts_len > 0 && args_len > 0)
		ft_printf(" ");
}

void	ft_echo(t_c *cmd)
{
	int	nl_req;

	if (!cmd)
		return ;
	nl_req = !valid_flag(cmd);
	print_words(cmd->opts, !nl_req);
	handle_space(cmd, nl_req);
	print_words(cmd->args, 0);
	print_nl(nl_req);
}
