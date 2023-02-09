/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 02:06:14 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/09 06:52:05 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*correct_path(char **paths, char *cmd)
{
	int		access_val;
	char	*complete_path;
	char	*tmp;
	int		i;

	i = 0;
	access_val = -1;
	complete_path = NULL;
	while (paths[i] && access_val)
	{
		tmp = ft_strjoin("/", cmd);
		complete_path = ft_strjoin(paths[i], tmp);
		free(tmp);
		access_val = access(complete_path, X_OK);
		if (access_val == 0)
			return (complete_path);
		free(complete_path);
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

	cmd_path = NULL;
	if (access(str, X_OK) != -1)
		return (str);
	env_path = env_value(env_lst, "PATH");
	if (!env_path || !ft_strlen(env_path))
	{
		if (env_path)
			free(env_path);
		return (cs_error(ERR_PATH, 127));
	}
	all_paths = split_paths(env_path);
	free(env_path);
	if (!all_paths)
		return (cs_error(ERR_CMD_FOUND, 127));
	cmd_path = correct_path(all_paths, str);
	return_free(all_paths, 0);
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
	opts = set_opts_exec(cmd);
	args = set_args_exec(cmd);
	res = malloc(sizeof(char *) * (2 + c_child(opts) + c_child(args)));
	res[0] = cmd_path;
	while (opts && opts[i])
	{
		res[i + 1] = ft_strdup(opts[i]);
		i++;
	}
	j = i;
	while (args && args[i - j])
	{
		res[i + 1] = ft_strdup(args[i - j]);
		i++;
	}
	res[i + 1] = NULL;
	dbl_exec_free(opts, args);
	return (res);
}

char	**custom_envp(t_env **env_lst)
{
	int		i;
	int		len;
	char	**res;
	t_env	*tmp;
	char	*tmp2;

	tmp = *env_lst;
	i = 0;
	len = ft_env_lst_size(*env_lst);
	res = (char **)malloc(sizeof(char *) * (len + 1));
	while (tmp)
	{
		tmp2 = ft_strjoin(tmp->name, "=");
		res[i] = ft_strjoin(tmp2, tmp->value);
		free(tmp2);
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
	char	**envp_lst;
	int		res_execve;

	args_str = NULL;
	envp_lst = NULL;
	res_execve = 0;
	cmd_path = get_cmd_path(env_lst, cmd.name);
	if (!cmd_path && !path_exec)
		return (ci_error(ERR_CMD_FOUND, 127));
	if (path_exec)
	{
		free(cmd_path);
		cmd_path = cmd.name;
	}
	args_str = execve_cmd(cmd, cmd_path);
	envp_lst = custom_envp(env_lst);
	res_execve = execve(cmd_path, args_str, envp_lst);
	return_free(args_str, 0);
	return_free(envp_lst, 0);
	return (res_execve);
}
