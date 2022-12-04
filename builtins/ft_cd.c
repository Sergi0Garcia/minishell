/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:04:51 by segarcia          #+#    #+#             */
/*   Updated: 2022/12/04 01:58:33 by segarcia         ###   ########.fr       */
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

static int	valid_options(char *opt)
{
	int	i;
	int	back_flag;

	i = 0;
	back_flag = 0;
	while (opt[i])
	{
		if (i < 2 && opt[i] == '-')
		{
			back_flag = 1;
			if (i == 1)
				back_flag = 0;
			i++;
		}
		else
		{
			if (opt[i] != 'L' && opt[i] != 'P')
				return (0);
		}
		i++;
	}
	if (back_flag)
		return (1);
	return (1);
}

static int	valid_flag(t_c *cmd)
{
	int		i;
	char	*option;

	if (!cmd || !cmd ->opts)
		return (1);
	i = 0;
	while (cmd->opts[i])
	{
		option[i] = cmd->opts[i];
		return (handle_error());
		i++;
	}
	return (1);
}

static int	handle_error(void)
{
	ft_printf("invalid option");
	ft_printf("\n");
	ft_printf("cd: usage: cd [-L|-P] [dir]");
	ft_printf("\n");
	return (0);
}

void	ft_cd(t_c *cmd, t_env_node **env_lst)
{
	char	*path;
	char	*str;
	char	pathname[PATH_MAX];
	int		valid;

	path = NULL;
	str = NULL;

	valid = valid_flag(cmd);
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
