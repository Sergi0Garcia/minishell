/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 02:06:14 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/05 02:53:21 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		return (cs_error(ERR_CMD_FOUND, 127));
	else
		return (complete_path);
}

char	*get_cmd_path(t_env **env_lst, char *str)
{
	char	*env_path;
	char	**all_paths;
	char	*cmd_path;

	if (access(str, X_OK) != -1)
		return (str);
	env_path = env_value(env_lst, "PATH");
	if (!env_path || !ft_strlen(env_path))
		return (cs_error(ERR_PATH, 127));
	all_paths = split_paths(env_path);
	if (!all_paths)
		return (cs_error(ERR_CMD_FOUND, 127));
	cmd_path = correct_path(all_paths, str);
	if (!cmd_path)
		return (NULL);
	return (cmd_path);
}

static char	**execve_cmd(t_ci cmd, char *cmd_path)
{
	char	**res;
	char	**opts;
	char	**args;
	int		i;
	int		j;

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
	j = i;
	while (args && args[i - j])
	{
		res[i + 1] = args[i - j];
		i++;
	}
	res[i + 1] = NULL;
	return (res);
}

char	**custom_envp(t_env **env_lst)
{
	int		i;
	int		len;
	char	**res;
	t_env	*tmp;

	tmp = *env_lst;
	i = 0;
	len = ft_env_lst_size(*env_lst);
	res = (char **)malloc(sizeof(char *) * (len + 1));
	while (tmp)
	{
		res[i] = ft_strjoin(tmp->name, "=");
		res[i] = ft_strjoin(res[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	ft_execve(t_ci cmd, t_env **env_lst, int path_exec)
{
	char	**args_str;
	char	*cmd_path;
	int		res_execve;

	args_str = NULL;
	cmd_path = get_cmd_path(env_lst, cmd.name);
	if (!cmd_path && !path_exec)
		return (ci_error(ERR_CMD_FOUND, 127));
	if (path_exec)
		cmd_path = cmd.name;
	args_str = execve_cmd(cmd, cmd_path);
	res_execve = execve(cmd_path, args_str, custom_envp(env_lst));
	return (res_execve);
}
