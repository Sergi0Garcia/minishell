/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 02:06:14 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/29 09:12:57 by rkanmado         ###   ########.fr       */
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
	int		i;
	int		count;
	char	**opts;
	char	**args;

	opts = ft_split(cmd->ci.opts, ' ');
	args = ft_split(cmd->ci.args, ' ');
	i = 0;
	count = 0;
	while (opts && opts[i])
		i++;
	count = i;
	i = 0;
	while (args && args[i])
		i++;
	count += i;
	return (count);
}

int child_nbr_str(char **str)
{
	int i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
// echo hello | grep hello

char	**execve_unifier(t_c *cmd, char *filename, int len)
{
	int		i;
	char	**res;
	char	**opts;
	char	**args;

	opts = ft_split(cmd->ci.opts, ' ');
	args = ft_split(cmd->ci.args, ' ');
	i = 0;
	res = (char **)malloc(sizeof(char *) * (len + 2));
	res[i++] = filename;
	while ((opts && opts[i - 1]) || (args && args[i - 1]))
	{
		if (opts && opts[i - 1])
			res[i] = opts[i - 1];
		else if (args && args[i - 1])
			res[i] = args[i - child_nbr_str(opts) - 1];
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	**path_execve_unifier(t_c *cmd, char *filename, int len)
{
	int		i;
	char	**res;
	char	**opts;
	char	**args;

	opts = ft_split(cmd->ci.opts, ' ');
	args = ft_split(cmd->ci.args, ' ');

	i = 0;
	res = (char **)malloc(sizeof(char *) * (len + 3));
	res[i++] = filename;
	res[i++] = cmd->ci.name;
	while ((opts && opts[i - 1]) || (args && args[i - 1]))
	{
		if (opts && opts[i - 1])
			res[i] = opts[i - 1];
		else if (args && args[i - 1])
			res[i] = args[i - child_nbr_str(opts) - 1];
		i++;
	}
	res[i] = NULL;
	return (res);
}

static char *get_cmd_path(t_env_node **env_lst, char *str)
{
	char    *env_path;
	char	**all_paths;
	char	*cmd_path;

	env_path = env_value(env_lst, "PATH");
	if (!env_path)
	{
		printf("no such file or directory\n");
		printf("%s", str);
		return (NULL);
	}
	all_paths = split_paths(env_path);
	if (!all_paths)
	{
		printf("no such file or directory here\n");
		return (NULL);
	}
	cmd_path = correct_path(all_paths, str);
	if (!cmd_path)
		return (NULL);
	return (cmd_path);
}

int ft_execve(t_c *cmd, t_env_node **env_lst)
{
	char	**execve_args;
	char	*cmd_path;
	int     i;
	int		opt_args_len;

	i = 0;
	execve_args = NULL;
	cmd_path = get_cmd_path(env_lst, cmd->ci.name);
	if (!cmd_path)
	{
		printf("command not found: %s\n", cmd->ci.name);
		return (EXIT_FAILURE);
	}
	opt_args_len = count_opts_args(cmd);
	execve_args = execve_unifier(cmd, cmd->ci.name, opt_args_len);
	execve(cmd_path, execve_args, NULL);
	return (EXIT_SUCCESS);
}

static int is_sh(char *str)
{
	int len;

	len = ft_strlen(str);
	if (len < 0 || len < 2)
		return (0);
	if (str[len - 1] == 'h'
		&& str[len - 2] == 's'
		&& str[len - 3] == '.')
			return (1);
	return (0);
}

int ft_path_execve(t_c *cmd, t_env_node **env_lst)
{
	char	**execve_args;
	char	*cmd_path;
	int		opt_args_len;

	cmd_path = NULL;
	execve_args = NULL;
	if (is_sh(cmd->ci.name))
	{
		cmd_path = get_cmd_path(env_lst, "bash");
		if (!cmd_path)
			return (EXIT_FAILURE);
		opt_args_len = count_opts_args(cmd);
		execve_args = path_execve_unifier(cmd, cmd_path, opt_args_len);
		execve(cmd_path, execve_args, NULL);
	}
	else
	{
		opt_args_len = count_opts_args(cmd);
		execve_args = path_execve_unifier(cmd, cmd_path, opt_args_len);
		execve(cmd->ci.name, execve_args, NULL);
	}
	return (EXIT_SUCCESS);
}
