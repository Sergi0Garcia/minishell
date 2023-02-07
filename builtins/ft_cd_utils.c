/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 02:35:07 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/07 11:56:05 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	back_flag(char *opt)
{
	int	len;

	if (!opt)
		return (0);
	len = ft_strlen(opt);
	if (len == 1 && opt[0] == '-')
		return (1);
	return (0);
}

static int	db_back_flag(char *opt)
{
	int	len;

	if (!opt)
		return (0);
	len = ft_strlen(opt);
	if (len < 2)
		return (0);
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
		{
			i++;
			continue ;
		}
		else
		{
			if (opt[i] != 'L' && opt[i] != 'P')
				return (0);
		}
		i++;
	}
	return (1);
}

int	return_free(char **opts, int st)
{
	int	len;
	int	i;

	i = 0;
	len = c_child(opts);
	while (i < len)
	{
		free(opts[i]);
		i++;
	}
	free(opts);
	return (st);
}

int	cd_valid_flag(t_c *cmd)
{
	int		i;
	char	**opts;

	opts = NULL;
	if (!cmd || !cmd->ci.opts)
		return (1);
	if (cmd->ci.opts)
		opts = ft_split(cmd->ci.opts, ' ');
	i = 0;
	while (opts && opts[i])
	{
		if (db_back_flag(opts[i]))
		{
			if (back_flag(opts[i + 1]))
				return (return_free(opts, 2));
			else
				return (return_free(opts, 1));
		}
		if (back_flag(opts[i]))
			return (return_free(opts, 2));
		if (!valid_options(opts[i]))
			return (return_free(opts, 0));
		i++;
	}
	return (return_free(opts, 1));
}

int	cd_handle_error(void)
{
	ft_printf("invalid option");
	ft_printf("\n");
	ft_printf("cd: usage: cd [-L|-P] [dir]");
	ft_printf("\n");
	return (EXIT_FAILURE);
}
