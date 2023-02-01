/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 02:39:04 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/01 06:07:46 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_env(char **envp, t_env **env_lst)
{
	int			i;
	int			brk_idx;
	char		*name;
	char		*val;
	t_env		*new;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		brk_idx = get_idx_separator(envp[i]);
		name = ft_substr(envp[i], 0, brk_idx);
		val = ft_substr(envp[i], brk_idx + 1, ft_strlen(envp[i]) - brk_idx - 1);
		new = ft_new_env_node(name, val);
		env_add_back(env_lst, new);
		i++;
	}
	return ;
}

void	update_env(t_env **env_lst, char *name, char *value)
{
	t_env	*tmp;

	tmp = *env_lst;
	while (tmp)
	{
		if (is_same_str(tmp->name, name))
		{
			free(tmp->value);
			tmp->value = value;
			env_lst = &tmp;
			return ;
		}
		tmp = tmp->next;
	}
}

void	new_env(t_env **env_lst, char *str)
{
	int			brk_idx;
	char		*name;
	char		*value;
	t_env		*new;

	brk_idx = get_idx_separator(str);
	if (brk_idx)
		name = ft_substr(str, 0, brk_idx);
	else
		name = ft_substr(str, 0, ft_strlen(str));
	value = NULL;
	if (brk_idx)
		value = ft_substr(str, brk_idx + 1, ft_strlen(str) - brk_idx - 1);
	if (exists_env(env_lst, name))
		return (update_env(env_lst, name, value));
	new = ft_new_env_node(name, value);
	env_add_back(env_lst, new);
	return ;
}

void	unset_env(t_env **env_lst, char *str)
{
	t_env	*current;
	t_env	*previous;
	t_env	*delete;

	current = *env_lst;
	previous = NULL;
	if (is_same_str((current)->name, str))
	{
		delete = current;
		current = current->next;
		free_env_node(&delete);
		*env_lst = current;
		return ;
	}
	while (current)
	{
		if (is_same_str((current)->name, str))
		{
			delete = current;
			previous->next = current->next;
			current = NULL;
			free_env_node(&delete);
			env_lst = &previous;
			return ;
		}
		previous = current;
		current = current->next;
	}
}
