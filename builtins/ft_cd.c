/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:04:51 by segarcia          #+#    #+#             */
/*   Updated: 2022/12/03 20:16:06 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	update_paths(t_env_node **env_lst, char *path, char	*pathname)
{
	new_env(env_lst, ft_strjoin("PWD=", path));
	new_env(env_lst, ft_strjoin("OLDPWD=", pathname));
}

static void	cd_back(t_env_node **env_lst)
{
	int		res_chdir;
	char	*old_path;
	char	*old_path_cp;
	char	pathname[PATH_MAX];

	old_path_cp = NULL;
	old_path = env_value(env_lst, "OLDPWD");
	if (!old_path)
	{
		ft_printf("cd: OLDPWD not set\n");
		return ;
	}
	// ft_pwd(NULL, pathname, PATH_MAX);
	res_chdir = chdir(old_path);
	if (res_chdir == -1)
		perror("Error: ");
	old_path_cp = ft_strdup(old_path);
	update_paths(env_lst, old_path, pathname);
	ft_printf("%s\n", old_path_cp);
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

static int	valid_options(t_c *cmd)
{
	char	*option;
	char	len;
	int		i;
	char	c;

	if (!cmd->opts)
		return (2);
	option = cmd->opts[0];
	len = ft_strlen(option);
	if (len == 1 && option[0] == '-')
		return (1);
	if (len == 2 && option[0] == '-' && option[1] == '-')
		return (2);
	i = 1;
	while (option[i])
	{
		c = option[i];
		if (c != 'L' && c != 'P')
		{
			ft_printf("invalid option: %c\n", c);
			ft_printf("cd: usage: cd [-L|-P] [dir]\n");
			return (0);
		}
		i++;
	}
	return (2);
}

void	ft_cd(t_c *cmd, t_env_node **env_lst)
{
	char	*path;
	char	*str;
	char	pathname[PATH_MAX];
	int		valid;

	path = NULL;
	str = NULL;

	valid = valid_options(cmd);
	ft_printf("valid: %i\n", valid);
	if (valid == 0)
		exit(EXIT_FAILURE);
	if (valid == 1)
		return (cd_back(env_lst));
	if (valid == 2)
	{
		path = get_home_address(env_lst);
		if (cmd->args && cmd->args[0][0] == '~')
		{
			str = ft_substr(str, 1, ft_strlen(str) - 1);
			path = ft_strjoin(path, str);
		}
		else
			path = cmd->args[0];
		// ft_pwd(NULL, pathname, PATH_MAX);
		ft_printf("Changing to path: %s\n", path);
		if (chdir(path) == -1)
			perror("Error: ");
		update_paths(env_lst, path, pathname);
	}
	return ;
}
