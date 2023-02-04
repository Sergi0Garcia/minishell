/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:14:59 by rkanmado          #+#    #+#             */
/*   Updated: 2023/02/04 10:03:44 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_status;

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
		sh->line = readline("\033[0;36mminishell$ \033[0m");
		if (sh->line == NULL)
		{
			write(1, "exit\n", 6);
			exit(EXIT_FAILURE);
		}
		if (ft_strlen(sh->line) > 0)
			add_history(sh->line);
		sh->line = ft_strtrim(sh->line, " ");
		lexing(sh);
		if (parser(sh))
		{
			expansion(sh);
			if (generate_cmd(sh))
				controller(sh);
		}
	}
	return ;
}

void	h_noninteractive_mode(t_minish *sh)
{
	sh->line = ft_strtrim(sh->argv[2], " ");
	lexing(sh);
	if (!parser(sh))
		return ;
	expansion(sh);
	generate_cmd(sh);
	return ;
}
