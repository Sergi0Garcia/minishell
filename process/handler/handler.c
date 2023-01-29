/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:14:59 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/29 21:50:07 by segarcia         ###   ########.fr       */
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
		sh->line = readline("@minishell-1.0$ ");
		sh->line = ft_strtrim(sh->line, " ");
		lexing(sh);
		if (parser(sh))
		{
			expansion(sh);
			if (generate_cmd(sh))
				controller(sh);
		}
		add_history(sh->line);
	}
	return ;
}

void	h_noninteractive_mode(t_minish *sh)
{
	no_interactive_mode_sig();
	sh->line = ft_strtrim(sh->argv[2], " ");
	lexing(sh);
	if (!parser(sh))
		return ;
	expansion(sh);
	generate_cmd(sh);
	return ;
}
