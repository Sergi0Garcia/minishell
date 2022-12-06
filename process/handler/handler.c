/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:14:59 by rkanmado          #+#    #+#             */
/*   Updated: 2022/12/06 21:01:20 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handler(t_minish *sh)
{
	if (sh->interactive)
		h_interactive_mode(sh);
	else
		h_noninteractive_mode(sh);
	return ;
}

void	h_interactive_mode(t_minish *sh)
{
	while (1)
	{
		interactive_mode_sig();
		sh->line = readline("---sh---");
		sh->line = ft_strtrim(sh->line, " ");
		lexing(sh);
	}
	return ;
}

void	h_noninteractive_mode(t_minish *sh)
{
	no_interactive_mode_sig();
	sh->line = ft_strtrim(sh->argv[2], " ");
	lexing(sh);
	// parse(sh);
	return ;
}
