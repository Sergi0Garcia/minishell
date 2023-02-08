/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 01:55:48 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/08 03:27:25 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**free_dp(char ***points)
{
	size_t	count;
	char	**tmp;

	count = 0;
	tmp = *points;
	while (tmp[count] != NULL)
	{
		printf("free %s", tmp[count]);
		free(tmp[count]);
		count++;
	}
	free(tmp);
	return (NULL);
}

void	free_kvp(t_kvp **kvp)
{
	int		i;
	t_kvp	*tmp;

	i = 0;
	tmp = *kvp;
	while (i < 13)
	{
		free(tmp[i].values.curr);
		free(tmp[i].values.next);
		i++;
	}
	free(tmp);
	return ;
}
