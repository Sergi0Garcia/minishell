/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 01:55:48 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/08 06:23:31 by rkanmado         ###   ########.fr       */
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

t_b	can_free(const t_wt *wt, t_wt key, int *i)
{
	int	count;

	count = 0;
	if (*i == 1)
		return (false);
	while (wt[count] != NEIN)
	{
		if (wt[count] == key)
		{
			*i = 1;
			return (true);
		}
		count++;
	}
	return (false);
}

void	free_tcn(t_cn *cn)
{
	free(cn->curr);
	free(cn->next);
	return ;
}

void	free_kvp(t_kvp **kvp)
{
	int		i;
	t_kvp	*tmp;
	int		rows[] = {0, 0, 0, 0, 0, 0, 0};

	i = 0;
	tmp = *kvp;
	while (i < 12)
	{
		if (can_free((const t_wt *)(t_wt[]){BEGINING, NEIN}, tmp[i].key, &rows[0]))
			free_tcn(&tmp[i].values);
		else if (can_free((const t_wt *)(t_wt[]){LESS, DLESS, GREAT, DGREAT, NEIN}, \
			tmp[i].key, &rows[1]))
			free_tcn(&tmp[i].values);
		else if (can_free((const t_wt *)(t_wt[]){WORD, NEIN}, tmp[i].key, &rows[2]))
			free_tcn(&tmp[i].values);
		else if (can_free((const t_wt *)(t_wt[]){PIPE, ORIF, ANDIF, NEIN}, \
			tmp[i].key, &rows[3]))
			free_tcn(&tmp[i].values);
		else if (can_free((const t_wt *)(t_wt[]){OPRARENTHESIS, NEIN}, tmp[i].key, \
			&rows[4]))
			free_tcn(&tmp[i].values);
		else if (can_free((const t_wt *)(t_wt[]){CPARENTHESIS, NEIN}, \
			tmp[i].key, &rows[5]))
			free_tcn(&tmp[i].values);
		else if (can_free((const t_wt *)(t_wt[]){END, NEIN}, tmp[i].key, &rows[6]))
			free_tcn(&tmp[i].values);
		i++;
	}
	free(tmp);
	return ;
}


