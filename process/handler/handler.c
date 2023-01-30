/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:14:59 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/30 12:42:44 by segarcia         ###   ########.fr       */
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
		sh->line = readline("minishell$ ");
		sh->line = ft_strtrim(sh->line, " ");
		lexing(sh);
		if (parser(sh))
		{
			expansion(sh);
			if (generate_cmd(sh))
			{
				g_status = controller(sh);
				waitpid(-1, &g_status, 0);
				waitpid(-1, &g_status, 0);
				waitpid(-1, &g_status, 0);
				if (g_status > 255)
					g_status = g_status / 255;
			}
		}
		add_history(sh->line);
		printf("g_status:%i\n", g_status);
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
