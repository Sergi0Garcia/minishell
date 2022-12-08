/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:04:51 by segarcia          #+#    #+#             */
/*   Updated: 2022/12/08 13:23:20 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	cd_back(t_env_node **env_lst)
{
	char	*path;
	char	*old_path;

	path = ft_pwd(NULL);
	old_path = env_value(env_lst, "OLDPWD");
	if (!old_path)
	{
		ft_printf("cd: OLDPWD not set\n");
		return ;
	}
	if (chdir(old_path) == -1)
		perror("");
	new_env(env_lst, ft_strjoin("PWD=", old_path));
	new_env(env_lst, ft_strjoin("OLDPWD=", path));
	ft_printf("%s\n", old_path);
}

static char	*get_home_address(t_env_node **env_lst)
{
	char	*home_path;
	char	*username;
	char	*res;

	home_path = env_value(env_lst, "HOME");
	if (home_path)
		return (home_path);
	username = env_value(env_lst, "USER");
	res = ft_strjoin("/Users/", username);
	return (res);
}

static char	*parse_home_dir(char *home_path, t_c *cmd)
{
	int		i;
	char	*res;
	char	*sub_str;

	i = 0;
	if (cmd && cmd->args && cmd->args[0])
	{
		if (cmd->args[0][0] && cmd->args[0][1]
			&& cmd->args[0][0] == '~' && cmd->args[0][1] == '/')
		{
			sub_str = ft_substr(cmd->args[0], 1, ft_strlen(cmd->args[0]));
			res = ft_strjoin(home_path, sub_str);
			return (res);
		}
		return (cmd->args[0]);
	}
	return (home_path);
}

static void	cd_default(t_env_node **env_lst, t_c *cmd)
{
	char	*path;
	char	*new_path;
	char	*home_path;

	path = ft_pwd(NULL);
	home_path = get_home_address(env_lst);
	new_path = parse_home_dir(home_path, cmd);
	if (chdir(new_path) == -1)
		perror("");
	new_env(env_lst, ft_strjoin("PWD=", new_path));
	new_env(env_lst, ft_strjoin("OLDPWD=", path));
}

/**
 * Function to handle command cd
 * @param cmd
 * @param env_lst
 */
void	ft_cd(t_c *cmd, t_env_node **env_lst)
{
	int		valid;

	valid = cd_valid_flag(cmd);
	if (valid == 0)
		return (cd_handle_error());
	if (valid == 2)
		return (cd_back(env_lst));
	if (valid == 1)
		return (cd_default(env_lst, cmd));
	return ;
}
