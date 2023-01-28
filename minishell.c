/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:43:34 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/28 02:41:39 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

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
	// handler(&sh);
	set_env(envp, &sh.env_lst);

	tester(&sh.env_lst);
	return (EXIT_SUCCESS);
}
