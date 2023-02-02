/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:03:44 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/02 14:02:46 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

int is_single_cmd(t_c *cmd)
{
	int i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	if (i == 1)
		return (1);
	else
		return (0);
}
	
int	is_single_execution(t_c *cmd)
{
	if (is_single_cmd(cmd)
	&& (is_same_str(cmd->ci.name, "exit")
	|| is_same_str(cmd->ci.name, "export")
	|| is_same_str(cmd->ci.name, "unset")
	|| is_same_str(cmd->ci.name, "cd")))
		return (1);
	return (0);
}

int is_file(char *str)
{
	int len;
	int i;

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
	}
	return (0);
}

int	file_validation(char *path)
{
	DIR *dir;

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