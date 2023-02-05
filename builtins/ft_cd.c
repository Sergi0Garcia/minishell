/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:04:51 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/05 13:41:20 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

static int	cd_back(t_env **env_lst)
{
	char	*path;
	char	*old_path;
	char	*tmp;

	path = ft_pwd(NULL, 0);
	old_path = env_value(env_lst, "OLDPWD");
	if (!old_path || !ft_strlen(old_path))
		return (EXIT_FAILURE);
	if (chdir(old_path) == -1)
	{
		perror("");
		return (EXIT_FAILURE);
	}
	tmp = ft_strjoin("PWD=", old_path);
	new_env(env_lst, tmp);
	free(tmp);
	tmp = ft_strjoin("OLDPWD=", path);
	new_env(env_lst, tmp);
	free(tmp);
	old_path = env_value(env_lst, "OLDPWD");
	ft_printf("%s\n", old_path);
	old_path = NULL;
	free(path);
	return (EXIT_SUCCESS);
}

static char	*get_home_address(t_env **env_lst)
{
	char	*home_path;
	char	*username;
	char	*res;
	char	*tmp;

	home_path = env_value(env_lst, "HOME");
	if (home_path && ft_strlen(home_path))
		return (home_path);
	username = env_value(env_lst, "USER");
	res = ft_strjoin("/Users/", username);
	tmp =  ft_strjoin("HOME=", res);
	new_env(env_lst, tmp);
	free(tmp);
	return (res);
}

static char	*parse_home_dir(char *home_path, t_c *cmd)
{
	int		i;
	char	*res;
	char	*sub_str;
	char	**args;
	char 	*tmp;

	args = NULL;
	if (cmd->ci.args)
		args = ft_split(cmd->ci.args, ' ');
	i = 0;
	if (cmd && args && args[0])
	{
		if (args[0][0] && args[0][0] == '~' && ft_strlen(args[0]) == 1)
		{
			return_free(args, 0);
			return (home_path);
		}
		if ((args[0][0] && args[0][1]
			&& args[0][0] == '~' && args[0][1] == '/'))
		{
			sub_str = ft_substr(args[0], 1, ft_strlen(args[0]));
			res = ft_strjoin(home_path, sub_str);
			free(sub_str);
			return_free(args, 0);
			return (res);
		}
		tmp = ft_strdup(args[0]);
		return_free(args, 0);
		return (tmp);
	}
	return (home_path);
}

static int	cd_default(t_env **env_lst, t_c *cmd)
{
	char	*path;
	char	*new_path;
	char	*home_path;
	char	*tmp;

	path = ft_pwd(NULL, 0);
	home_path = get_home_address(env_lst);
	new_path = parse_home_dir(home_path, cmd);
	if (chdir(new_path) == -1)
	{
		perror("");
		return (EXIT_FAILURE);
	}
	tmp = ft_strjoin("OLDPWD=", path);
	new_env(env_lst, tmp);
	free(tmp);
	free(path);
	path = ft_pwd(NULL, 0);
	tmp = ft_strjoin("PWD=", path);
	new_env(env_lst, tmp);
	free(path);
	free(tmp);
	free(home_path);
	free(new_path);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_c *cmd, t_env **env_lst)
{
	int		valid;

	valid = cd_valid_flag(cmd);
	if (valid == 0)
		return (cd_handle_error());
	if (valid == 2)
		return (cd_back(env_lst));
	if (valid == 1)
		return (cd_default(env_lst, cmd));
	return (EXIT_SUCCESS);
}
