/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 02:06:14 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/31 11:51:44 by segarcia         ###   ########.fr       */
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

int child_nbr_str(char **str)
{
	int i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*get_cmd_path(t_env **env_lst, char *str)
{
	char	*env_path;
	char	**all_paths;
	char	*cmd_path;

	env_path = env_value(env_lst, "PATH");
	if (!env_path)
		return (cs_error(ERR_PATH, 127));
	all_paths = split_paths(env_path);
	if (!all_paths)
		return (cs_error(ERR_CMD_FOUND, 127));
	cmd_path = correct_path(all_paths, str);
	if (!cmd_path)
		return (NULL);
	return (cmd_path);
}

static int	c_child(char **str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

static char **execve_cmd(t_ci cmd, char *cmd_path)
{
	char	**res;
	char	**opts;
	char	**args;
	int		i;

	i = 0;
	opts = ft_split(cmd.opts, ' ');
	args = ft_split(cmd.args, ' ');
	res = malloc(sizeof(char *) * (2 + c_child(opts) + c_child(args)));
	res[0] = cmd_path;
	while (opts && opts[i])
	{
		res[i + 1] = opts[i];
		i++;
	}
	while (args && args[i])
	{
		res[i + 1] = args[i];
		i++;
	}
	res[i + 1] = NULL;
	return (res);
}

int	ft_execve(t_ci cmd, t_env **env_lst, int path_exec)
{
	char	**args_str;
	char	*cmd_path;

	args_str = NULL;
	cmd_path = get_cmd_path(env_lst, cmd.name);
	if (!cmd_path && !path_exec)
		return (ci_error(ERR_CMD_FOUND, 127));
	if (path_exec)
		cmd_path = cmd.name;
	args_str = execve_cmd(cmd, cmd_path);
	execve(cmd_path, args_str, NULL);
	return (EXIT_SUCCESS);
}

// static int is_sh(char *str)
// {
// 	int len;

// 	len = ft_strlen(str);
// 	if (len < 0 || len < 2)
// 		return (0);
// 	if (str[len - 1] == 'h'
// 		&& str[len - 2] == 's'
// 		&& str[len - 3] == '.')
// 			return (1);
// 	return (0);
// }

// int ft_path_execve(t_c *cmd, t_env **env_lst)
// {
// 	char	**execve_args;
// 	char	*cmd_path;
// 	int		opt_args_len;

// 	cmd_path = NULL;
// 	execve_args = NULL;
// 	if (is_sh(cmd->ci.name))
// 	{
// 		cmd_path = get_cmd_path(env_lst, "bash");
// 		if (!cmd_path)
// 			return (EXIT_FAILURE);
// 		opt_args_len = count_opts_args(cmd);
// 		execve_args = path_execve_unifier(cmd, cmd_path, opt_args_len);
// 		execve(cmd_path, execve_args, NULL);
// 	}
// 	else
// 	{
// 		opt_args_len = count_opts_args(cmd);
// 		execve_args = path_execve_unifier(cmd, cmd_path, opt_args_len);
// 		execve(cmd->ci.name, execve_args, NULL);
// 	}
// 	return (EXIT_SUCCESS);
// }