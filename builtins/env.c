/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 09:33:02 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/27 15:44:41 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	exists_env(t_env_node **env_lst, char *str)
{
	int			found;
	t_env_node	*tmp;

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
		name = ft_substr(envp[i], 0, brk_idx);
		value = ft_substr(envp[i], brk_idx + 1, ft_strlen(envp[i]) - brk_idx - 1);
		new = ft_new_env_node(name, value);
		env_add_back(env_lst, new);
		i++;
	}
	return ;
}

void	update_env(t_env_node **env_lst, char *name, char *value)
{
	t_env_node	*tmp;

	tmp = *env_lst;
	while (tmp)
	{
		if (is_same_str(tmp->name, name))
		{
			free(tmp->value);
			tmp->value = value;
			*env_lst = tmp;
			return ;
		}
		tmp = tmp->next;
	}
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
	name = ft_substr(str, 0, brk_idx);
	value = ft_substr(str, brk_idx + 1, ft_strlen(str) - brk_idx - 1);
	if (exists_env(env_lst, name))
		return(update_env(env_lst, name, value));
	new = ft_new_env_node(name, value);
	env_add_back(env_lst, new);
	return ;
}

static void	free_env_node(t_env_node **env)
{
	(*env)->next = NULL;
	free((*env)->name);
	free((*env)->value);
	free(*env);
	*env = NULL;
}

void	unset_env(t_env_node **env_lst, char *str)
{
	t_env_node	*current;
	t_env_node	*previous;
	t_env_node	*delete;

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

void	print_env(t_env_node **env_lst, int	with_declare)
{
	t_env_node	*tmp;

	tmp = *env_lst;
	while (tmp)
	{
		if (with_declare)
		{
			ft_printf("declare -x ");
			ft_printf("%s=\"%s\"\n", tmp->name, tmp->value);
		}
		else
			ft_printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}
