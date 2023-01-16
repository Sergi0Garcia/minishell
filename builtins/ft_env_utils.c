/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:22:12 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/16 10:51:19 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

char	*env_value(t_env_node **env_lst, char *name)
{
	t_env_node	*tmp;

	tmp = *env_lst;
	if (exists_env(env_lst, name))
	{
		while (tmp)
		{
			if (is_same_str(tmp->name, name))
				return (tmp->value);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

void	set_env(char **envp, t_env_node **env_lst)
{
	int			i;
	int			brk_idx;
	char		*name;
	char		*val;
	t_env_node	*new;

	i = 0;
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
			env_lst = &tmp;
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

void	print_env(t_env_node **env_lst, int with_declare)
{
	t_env_node	*tmp;

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
