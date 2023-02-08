/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:22:12 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/07 04:15:25 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	exists_env(t_env **env_lst, char *str)
{
	int		found;
	t_env	*tmp;

	found = 0;
	tmp = *env_lst;
	while (tmp)
	{
		if (is_same_str(tmp->name, str))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static char	*get_special_env(char *name)
{
	char	*res;

	res = "";
	if (*name == '$')
		res = ft_itoa(getpid());
	else if (*name == '?')
		res = ft_itoa(g_status);
	return (res);
}

char	*env_value(t_env **env_lst, char *name)
{
	t_env	*tmp;
	char	*res;

	res = get_special_env(name);
	if (ft_strlen(res) > 0)
		return (res);
	tmp = *env_lst;
	if (env_lst == NULL)
		return (ft_strdup(""));
	if (exists_env(env_lst, name))
	{
		while (tmp)
		{
			if (is_same_str(tmp->name, name))
			{
				if (!tmp->value || tmp->value == NULL)
					return (ft_strdup(""));
				return (ft_strdup(tmp->value));
			}
			tmp = tmp->next;
		}
	}
	return (res);
}

void	print_env(t_env **env_lst, int with_declare)
{
	t_env	*tmp;

	if (!env_lst)
		return ;
	tmp = *env_lst;
	while (tmp)
	{
		if (with_declare)
		{
			ft_printf("declare -x ");
			ft_printf("%s", tmp->name);
			if (tmp->value)
			{
				ft_printf("=\"%s\"\n", tmp->value);
			}
			else
				ft_printf("\n");
		}
		else
		{
			if (tmp->value)
				ft_printf("%s=%s\n", tmp->name, tmp->value);
		}
		tmp = tmp->next;
	}
}
