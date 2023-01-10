/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 06:10:16 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/10 06:10:52 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_wt	*alloc(t_wt	**wt, int mem_nbr)
{
	*wt = malloc(sizeof(t_wt) * mem_nbr);
	if (*wt == NULL)
		error("Memory allocation failed");
	return (*wt);
}
