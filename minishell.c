/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:43:34 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/26 20:28:37 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	interactive(t_minish *sh)
{
	read_line(sh);
	parse(sh);
	return ;
}

void	non_interactive(t_minish *sh)
{
	parse(sh);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_minish	sh;

	(void) argc;
	(void) argv;
	(void) envp;
	check_usage(argc, argv, &sh);
	init(&sh, argv, envp);
	read_line(&sh);
	return (1);
}
