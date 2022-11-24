/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:43:34 by segarcia          #+#    #+#             */
/*   Updated: 2022/11/24 11:17:23 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char **env_vars;

	(void) argc;
	(void) argv;
	(void) envp;
	ft_pwd();
	env_vars = set_env(envp);
	return (1);
}
