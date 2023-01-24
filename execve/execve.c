/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 02:06:14 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/23 03:33:17 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**split_paths(char *path)
{
	char	**paths;

	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*correct_path(char **paths, char *cmd)
{
	int		access_val;
	char	*complete_path;
	int		i;

	i = 0;
	access_val = -1;
	while (paths[i] && access_val)
	{
		complete_path = ft_strjoin("/", cmd);
		complete_path = ft_strjoin(paths[i], complete_path);
		access_val = access(complete_path, X_OK);
		i++;
	}
	if (access_val == -1)
		return (NULL);
	else
		return (complete_path);
}

int	count_opts_args(t_c *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd->opts && cmd->opts[i])
		i++;
	count = i;
	i = 0;
	while (cmd->args && cmd->args[i])
		i++;
	count += i;
	return (count);
}

char	**execve_unifier(t_c *cmd, char *filename, int len)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 1;
	res = (char **)malloc(sizeof(char *) * (len + 2));
	res[0] = filename;
	if (len == 0)
	{
		res[1] = NULL;
		return (res);
	}
	while (cmd->opts[i])
	{
		res[j] = cmd->opts[i];
		ft_printf("res[%i] = %s\n", i, cmd->opts[i]);
 		i++;
		j++;
	}
	j = i;
	i = 0;
	while (cmd->args[i])
	{
		res[j + i] = cmd->args[i];
		ft_printf("res[%i] = %s\n", j + i,  cmd->args[i]);
		i++;
	}
	res[j + i] = NULL;
	ft_printf("res[%i] = %s\n", j + i, NULL);

	i = 0;
	while (res[i])
	{
		ft_printf(":: %s\n", res[i]);
		i++;
	}
	return (res);
}

int ft_execve(t_env_node **env_lst, t_c *cmd)
{
	char	**execve_args;
	char	*cmd_path;
	char    *env_path;
	char	**all_paths;
	int     i;
	int		opt_args_len;

	i = 0;
	execve_args = NULL;
	env_path = env_value(env_lst, "PATH");
	if (!env_path)
		return (EXIT_FAILURE);
	all_paths = split_paths(env_path);
	if (!all_paths)
		return (EXIT_FAILURE);
	cmd_path = correct_path(all_paths, cmd->name);
	opt_args_len = count_opts_args(cmd);
	execve_args = execve_unifier(cmd, cmd_path, opt_args_len);
	execve(cmd_path, execve_args, NULL);
	return (EXIT_SUCCESS);
}
