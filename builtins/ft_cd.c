/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:04:51 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/29 01:28:11 by segarcia         ###   ########.fr       */
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
	ft_pwd(pathname, PATH_MAX);
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

void	ft_cd(char *str, t_env_node **env_lst)
{
	char	*path;
	int		res;
	int		i;
	char	pathname[PATH_MAX];

	i = 0;
	path = str;
	if (str[i] == '-')
		return (cd_back(env_lst));
	if (str[i] == '~')
	{
		str = ft_substr(str, 1, ft_strlen(str) - 1);
		path = ft_strjoin(get_home_address(env_lst), str);
	}
	ft_pwd(pathname, PATH_MAX);
	res = chdir(path);
	if (res == -1)
		perror("Error: ");
	new_env(env_lst, ft_strjoin("PWD=", path));
	new_env(env_lst, ft_strjoin("OLDPWD=", pathname));
	return ;
}
