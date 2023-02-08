/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:51:02 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/08 04:30:33 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	c_child(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	**split_paths(char *path)
{
	char	**paths;

	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

void	dbl_exec_free(char **opts, char **args)
{
	if (opts)
		return_free(opts, 0);
	if (args)
		return_free(args, 0);
}

char	**set_opts_exec(t_ci cmd)
{
	if (cmd.opts && ft_strlen(cmd.opts))
		return (ft_split(cmd.opts, ' '));
	return (NULL);
}

char	**set_args_exec(t_ci cmd)
{
	if (cmd.args && ft_strlen(cmd.args))
		return (ft_split(cmd.args, ' '));
	return (NULL);
}
