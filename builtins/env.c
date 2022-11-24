/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 09:33:02 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/24 13:20:56 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**set_env(char **envp)
{
	int	i;
	int j;
	int	len;
	int	total_len;
	char **res;

	i = 0;
	while (envp[i])
		i++;
	total_len = i;
	res = (char **)(malloc(sizeof(char *) * (total_len + 1)));
	i = 0;
	while (i < total_len)
	{
		len = ft_strlen(envp[i]);
		res[i] = (char *)malloc(sizeof(char) * (len + 1));
		j = 0;
		while (j < len)
		{
			res[i][j] = envp[i][j];
			j++;
		}
		res[i][j] = '\0';
		i++;
	}
	res[i] = NULL;
	return (res);
}
