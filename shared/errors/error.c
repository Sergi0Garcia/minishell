/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:01:44 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/05 05:22:02 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_b	can_add_backtic(char *command)
{
	if (ft_strcmp(command, "export") == 0 \
		|| ft_strcmp(command, "unset") == 0)
		return (true);
	return (false);
}

void	errormsg(char *command, char *text)
{
	char	*msg;

	msg = NULL;
	if (command == NULL)
		joinstrs(msg, command);
	joinstrs(msg, ": ");
	if (can_add_backtic(command) == true)
		joinstrs(msg, "`");
	if (can_add_backtic(command) == false)
		joinstrs(msg, "'");
	joinstrs(msg, ": ");
	joinstrs(msg, text);
	ft_putstr_fd(msg, 2);
	free(msg);
	return ;
}

char	*joinstrs(char *s1, char *s2)
{
	char	*result;
	int		len;

	if (s1 == NULL)
	{
		s1 = malloc(sizeof(char));
		if (s1 == NULL)
			return (NULL);
		*s1 = '\0';
	}
	if (s2 == NULL)
		return (NULL);
	len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	result = malloc(len * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, ft_strlen(s1));
	ft_strlcat(result, s2, ft_strlen(s2));
	free(s1);
	return (result);
}

void	error(char *str)
{
	write(2, str, ft_strlen(str));
	system("leaks ./minishell");
	exit(EXIT_FAILURE);
	return ;
}
