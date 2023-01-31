/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:07:34 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/30 01:03:46 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env(t_ci cmd, t_env **env_lst)
{
	(void) cmd;
	print_env(env_lst, 0);
	return (EXIT_SUCCESS);
}
