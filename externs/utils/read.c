/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:53:33 by rkanmado          #+#    #+#             */
/*   Updated: 2022/11/24 17:19:42 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	read(t_minish *sh)
{
	while (1)
	{
		sh->line = readline("---sh--- !");
		if (sh->line == NULL)
			break;
		add_history(sh->line);
		parse(sh);
	}
}
