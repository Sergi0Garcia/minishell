/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:43:34 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/27 02:07:45 by segarcia         ###   ########.fr       */
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

	t_env_node	*env_lst;
	env_lst = NULL;
	set_env(envp, &env_lst);
	tester(&env_lst);
	// playground();
	return (EXIT_SUCCESS);
}
