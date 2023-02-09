/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:03:44 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/09 06:23:24 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_file(char *str)
{
	int	len;
	int	i;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len < 2)
		return (0);
	if (str[0] != '.')
		return (0);
	i = 1;
	while (i < len)
	{
		if (str[i] == '.')
			i++;
		else if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static int	is_builtin(char *str)
{
	if (is_same_str(str, "exit")
		|| is_same_str(str, "echo")
		|| is_same_str(str, "cd")
		|| is_same_str(str, "pwd")
		|| is_same_str(str, "export")
		|| is_same_str(str, "unset")
		|| is_same_str(str, "env"))
		return (1);
	return (0);
}

int	file_validation(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		ci_error(ERR_IS_DR, 126);
		closedir(dir);
		return (0);
	}
	if (access(path, F_OK) == -1)
	{
		ci_error(ERR_PATH, 127);
		return (0);
	}
	if (access(path, R_OK) == -1
		|| access(path, X_OK) == -1)
	{
		ci_error(ERR_PERMISSION, 126);
		return (0);
	}
	return (1);
}

int	valid_fork(t_c *cmds, t_env **env_lst)
{
	t_ci	cmd;
	char	*cmd_path;

	cmd = cmds->ci;
	if (!cmd.name || !ft_strlen(cmd.name))
		return (0);
	if ((cmd.infile == -1 || cmd.outfile == -2) && (cmds->next))
		return (1);
	if ((cmd.infile == -1 || cmd.outfile == -1))
		return (0);
	if (is_builtin(cmd.name))
		return (1);
	if (is_file(cmd.name))
		return (file_validation(cmd.name));
	cmd_path = get_cmd_path(env_lst, cmd.name);
	if (!cmd_path)
		return (0);
	if (!is_same_str(cmd_path, cmd.name))
		free(cmd_path);
	return (1);
}
