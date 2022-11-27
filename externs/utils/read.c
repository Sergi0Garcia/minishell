/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:53:33 by rkanmado          #+#    #+#             */
/*   Updated: 2022/11/27 17:10:46 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	read_line(t_minish *sh)
{
	sh->line = readline("---sh---");
	if (sh->line == NULL)
		return ;
	add_history(sh->line);
	return ;
}
