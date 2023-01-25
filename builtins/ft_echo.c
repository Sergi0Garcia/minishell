/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:59:06 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/25 03:25:00 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	valid_flag(t_c *cmd)
{
	int		i;
	char	**opts;

	opts = ft_split(cmd->ci.opts, ' ');
	if (!opts || !opts[0])
		return (0);
	if (opts[0][0] != '-')
		return (0);
	if (opts[0][1] != 'n')
		return (0);
	i = 2;
	while (opts[0][i])
	{
		if (opts[0][i] != 'n')
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
	int		args_len;
	int		opts_len;
	int		i;
	char	**opts;
	char	**args;

	opts = ft_split(cmd->ci.opts, ' ');
	args = ft_split(cmd->ci.args, ' ');

	i = -1;
	while (args && args[++i])
	args_len = i;
	i = -1;
	while (opts && opts[++i])
	opts_len = i - !nl_req;
	if (opts_len > 0 && args_len > 0)
		ft_printf(" ");
}

void	ft_echo(t_c *cmd)
{
	int		nl_req;
	char	**opts;
	char	**args;

	opts = ft_split(cmd->ci.opts, ' ');
	args = ft_split(cmd->ci.args, ' ');
	if (!cmd)
		return ;
	nl_req = !valid_flag(cmd);
	print_words(opts, !nl_req);
	handle_space(cmd, nl_req);
	print_words(args, 0);
	print_nl(nl_req);
}
