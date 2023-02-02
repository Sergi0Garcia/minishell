/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:03:04 by segarcia          #+#    #+#             */
/*   Updated: 2023/02/02 14:26:28 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

extern int	g_status;

static void print_message(t_err type)
{
    if (type == ERR_NONE)
        return ;
    if (type == ERR_PIPE)
        ft_printf("minishell: error creating pipe\n");
    else if (type == ERR_FORK)
        ft_printf("minishell: error creating fork\n");
    else if (type == ERR_PATH)
        ft_printf("minishell: no such file or directory\n");
    else if (type == ERR_CMD_FOUND)
        write(2, "minishell: command not found\n", 29); 
    else if (type == ERR_DUP2)
        ft_printf("minishell: error in dup2\n"); 
    else if (type == ERR_PERMISSION)
        ft_printf("minishell: error permission denied\n");
    else if (type == ERR_IS_DR)
        ft_printf("minishell: error is directory\n");
}

int ci_error(t_err type, int err)
{
	g_status = err;
    print_message(type);
	return (err);
}

char    *cs_error(t_err type, int err)
{
    g_status = err;
    print_message(type);
	return (NULL);
}
