/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:09:01 by segarcia          #+#    #+#             */
/*   Updated: 2023/01/17 13:31:59 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

/**
 * Controller function to execute each cmd
 * It executes with execve | builtin function depending the case
 * @param cmd 
 * @return int 
 */
int controller(t_c *cmd)
{
    (void) cmd;
    return (EXIT_SUCCESS);
}