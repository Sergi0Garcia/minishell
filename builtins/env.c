/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 09:33:02 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/27 01:42:59 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int get_idx_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

static void copy_str(char *dst, char *src, int idx_i, int idx_f)
{
	int	i;
	int	j;

	i = 0;
	j = idx_i;
	if (!dst || !src)
		return ;
	while (j <= idx_f)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
}

void set_env(char **envp, t_env_node **env_lst)
{
	int			i;
	int			brk_idx;
	char		*name;
	char		*value;
	t_env_node	*new;

	i = 0;
	while (envp[i])
	{
		brk_idx = get_idx_equal_sign(envp[i]);
		name = malloc(sizeof(char) * (brk_idx) + 1);
		value = malloc(sizeof(char) * (ft_strlen(envp[i]) - brk_idx));
		copy_str(name, envp[i], 0, brk_idx - 1);
		copy_str(value, envp[i], brk_idx + 1, ft_strlen(envp[i]) - 1);
		new = ft_new_env_node(name, value);
		env_add_back(env_lst, new);
		i++;
	}
	return ;
}

void	new_env(t_env_node **env_lst, char *str)
{
	int			brk_idx;
	char		*name;
	char		*value;
	t_env_node	*new;

	brk_idx = get_idx_equal_sign(str);
	if (!brk_idx)
		return ;
	name = malloc(sizeof(char) * (brk_idx) + 1);
	value = malloc(sizeof(char) * (ft_strlen(str) - brk_idx));
	copy_str(name, str, 0, brk_idx - 1);
	copy_str(value, str, brk_idx + 1, ft_strlen(str) - 1);
	new = ft_new_env_node(name, value);
	env_add_back(env_lst, new);
	return ;
}

int	is_same_str(char *str1, char *str2)
{
	int i;

	if (!str1 || !str2)
		return (0);
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

void	unset_env(t_env_node **env_lst, char *str)
{
	t_env_node	*tmp;
	t_env_node	*last;
	t_env_node	*to_delete;
	int			i;
	int			len;

	tmp = *env_lst;
	last = ft_env_last(tmp);
	i = 0;
	len = 0;
	// first occurrence
	if (is_same_str((tmp)->name, str))
	{
		to_delete = tmp;
		tmp = tmp->next;
		*env_lst = tmp;
		return ;
	}
	if (last && is_same_str(last->name, str))
	{
		len = ft_env_lst_size(tmp);
		while(tmp)
		{
			if (len == 1)
			{
				// free initial;
				*env_lst = NULL;
				return ;
			}
			i++;
			if (i == len - 1)
			{
				tmp->next = tmp->next->next;
				env_lst = &tmp;
				return ;
			}
			tmp = tmp->next;
		}
	}
	while (tmp)
	{
		if (tmp->next && is_same_str((tmp)->next->name, str))
		{
			tmp->next = tmp->next->next;
			env_lst = &tmp;
			return ;
		}
		tmp = tmp->next;
	}
	env_lst = &tmp;
}
