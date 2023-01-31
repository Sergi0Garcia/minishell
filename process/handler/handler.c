/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:14:59 by rkanmado          #+#    #+#             */
/*   Updated: 2023/01/31 11:30:17 by segarcia         ###   ########.fr       */
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
	int i;

	while (1)
	{
		interactive_mode_sig();
		sh->line = readline("minishell$ ");
		if (sh->line == NULL)
		{
			write(1, "exit\n", 6);
			exit(EXIT_FAILURE);
		}
		sh->line = ft_strtrim(sh->line, " ");
		lexing(sh);
		if (parser(sh))
		{
			expansion(sh);
			if (generate_cmd(sh))
			{
				i = 0;
				g_status = controller(sh);
				while (i < sh->cmds.size)
				{
					waitpid(-1, &g_status, 0);
					i++;
				}
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
	sh->line = ft_strtrim(sh->argv[2], " ");
	lexing(sh);
	if (!parser(sh))
		return ;
	expansion(sh);
	generate_cmd(sh);
	return ;
}
