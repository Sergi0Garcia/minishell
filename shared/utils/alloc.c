/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 06:10:16 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/09 03:52:08 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_wt	*alloc(int mem_nbr)
{
	t_wt	*wt;

	wt = malloc(sizeof(t_wt) * mem_nbr);
	if (wt == NULL)
		error("Memory allocation failed");
	return (wt);
}

t_wt	*duptwt(const t_wt *s1)
{
	t_wt		*cpy;
	size_t		i;

	i = 0;
	while (s1[i] != NEIN)
		i++;
	cpy = (t_wt *)malloc(sizeof(t_wt) * (i + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (s1[i] != NEIN)
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = NEIN;
	return (cpy);
}

void	*ft_cpywt(t_wt **dst, const void *src, size_t n)
{
	const t_wt	*s;
	t_wt		*d;
	size_t		i;

	s = src;
	d = *dst;
	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
