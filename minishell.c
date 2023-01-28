/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:43:34 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/28 00:02:42 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

// void	interactive(t_minish *sh)
// {
// 	read_line(sh);
// 	parse(sh);
// 	return ;
// }

// void	non_interactive(t_minish *sh)
// {
// 	parse(sh);
// 	return ;
// }

int	main(int argc, char **argv, char **envp)
{
	t_minish	sh;

	(void) sh;
	(void) argc;
	(void) argv;
	(void) envp;

	init(&sh, argv);
	check_usage(argc, argv, &sh);
	// check_usage(argc, argv, &sh);
	// init(&sh, argv, envp);
	// check_usage(argc, argv, &sh);
	handler(&sh);

	set_env(envp, &sh.env_lst);
	tester(sh.env_lst);
	// playground();
	return (EXIT_SUCCESS);
}
