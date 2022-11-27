/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:04:51 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/27 20:05:37 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * We need to handle following case
 * cd - (Search for $LASTPWD)
 * cd ~ (append $HOME)
 * @param str
 */
void	ft_cd(char *str, t_env_node **env_lst)
{
	char	*path;
	int 	res;
	int		i;
	char	pathname[PATH_MAX];

	i = 0;

	if (str[i] == '-')
	{
		path = env_value(env_lst, "OLDPWD");
		if (!path)
		{
			ft_printf("cd: OLDPWD not set\n");
			return ;
		}
	}
	if (str[i] == '~')
	{
		path = env_value(env_lst, "HOME");
		if (!path)
		{
			ft_printf("cd: HOME not set\n");
			return ;
		}
		str = ft_substr(str, 1, ft_strlen(str) - 1);
		path = ft_strjoin(path, str);
		printf("path: %s\n", path);
	}
	ft_pwd(pathname, PATH_MAX);
	res = chdir(path);
	if (res == -1)
		 perror("Error: ");
	// printf("%s\n", ft_strjoin("PWD=", path));
	new_env(env_lst, ft_strjoin("PWD=", path));
	new_env(env_lst, ft_strjoin("OLDPWD=", pathname));
	return ;
}