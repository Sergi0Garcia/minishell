/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:43:34 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/29 22:22:58 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	g_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_minish	sh;

	init(&sh, argv);
	check_usage(argc, argv, &sh);
	set_env(envp, &sh.env_lst);
	handler(&sh);
	return (EXIT_SUCCESS);
}
