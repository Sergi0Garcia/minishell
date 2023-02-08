/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkanmado <rkanmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:43:34 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/08 03:17:06 by rkanmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	g_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_minish	sh;

	(void) envp;
	init(&sh, argv);
	check_usage(argc, argv, &sh);
	set_env(envp, &sh.env_lst);
	handler(&sh);
	return (g_status);
}
