/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:53:33 by rkanmado          #+#    #+#             */
/*   Updated: 2022/11/26 20:24:23 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	read_line(t_minish *sh)
{
	int	loop;

	loop = 1;
	while (loop == 1)
	{
		sh->line = readline("---sh--- !");
		if (sh->line == NULL)
			break ;
		printf("%s", sh->line);
		add_history(sh->line);
		parse(sh);
	}
	return ;
}
